#include "flecs_private.h"

ecs_stream_t ecs_stream_open(
    ecs_world_t *world,
    ecs_snapshot_t *snapshot)
{
    return (ecs_stream_t){
        .world = world,
        .reader.cur = EcsComponentSegment,
        .reader.tables = snapshot->tables
    };
}

void ecs_stream_close(
    ecs_stream_t *stream)
{ }

static
void ecs_component_reader_fetch_component_data(
    ecs_stream_t *stream)
{
    ecs_component_reader_t *reader = &stream->reader.component;
    ecs_world_t *world = stream->world;
    ecs_chunked_t *tables = world->main_stage.tables;

    /* Component table is the first table in the world */
    ecs_table_t *table = ecs_chunked_get(tables, ecs_table_t, 0);
    reader->id_column = ecs_vector_first(table->columns[0].data);
    reader->data_column = ecs_vector_first(table->columns[1].data);
    reader->name_column = ecs_vector_first(table->columns[2].data);
    reader->count = ecs_vector_count(table->columns[0].data);
}

static
void ecs_component_reader_next(
    ecs_stream_t *stream)
{
    ecs_component_reader_t *reader = &stream->reader.component;

    switch(reader->cur) {
    case EcsComponentHeader:  
        reader->cur = EcsComponentId;
        if (!reader->id_column) {
            ecs_component_reader_fetch_component_data(stream);
            reader->index = 0;
        }
        break;

    case EcsComponentId:
        reader->cur = EcsComponentSize;
        break;

    case EcsComponentSize:
        reader->cur = EcsComponentNameLength;
        reader->name = reader->name_column[reader->index];
        reader->len = strlen(reader->name) + 1; 
        break;

    case EcsComponentNameLength:
        reader->cur = EcsComponentName;
        reader->written = 0;
        break;

    case EcsComponentName:
        reader->cur = EcsComponentHeader;    
        reader->index ++;
        if (reader->index == reader->count) {
            stream->reader.cur = EcsTableSegment;
        }
        break;

    default:
        ecs_abort(ECS_INTERNAL_ERROR, NULL);        
    }
}

static
size_t ecs_component_reader(
    void *buffer,
    size_t size,
    ecs_stream_t *stream)
{
    if (!size) {
        return 0;
    }

    if (size < sizeof(int32_t)) {
        return -1;
    }

    ecs_component_reader_t *reader = &stream->reader.component;
    size_t read = 0;

    if (!reader->cur) {
        reader->cur = EcsComponentHeader;
    }

    switch(reader->cur) {
    case EcsComponentHeader:  
        *(ecs_blob_header_kind_t*)buffer = EcsComponentHeader;
        read = sizeof(ecs_blob_header_kind_t);
        ecs_component_reader_next(stream);
        break;

    case EcsComponentId:
        *(int32_t*)buffer = (int32_t)reader->id_column[reader->index];
        read = sizeof(int32_t);
        ecs_component_reader_next(stream);
        break;

    case EcsComponentSize:
        *(int32_t*)buffer = (int32_t)reader->data_column[reader->index].size;
        read = sizeof(int32_t);
        ecs_component_reader_next(stream);
        break;

    case EcsComponentNameLength:
        *(int32_t*)buffer = (int32_t)reader->len;
        read = sizeof(int32_t);
        ecs_component_reader_next(stream);    
        break;

    case EcsComponentName:
        read = reader->len - reader->written;
        if (read > size) {
            read = size;
        }
        
        memcpy(buffer, ECS_OFFSET(reader->name, reader->written), read);
        reader->written += read;

        ecs_assert(reader->written <= reader->len, ECS_INTERNAL_ERROR, NULL);

        if (reader->written == reader->len) {
            ecs_component_reader_next(stream);
        }
        break;

    default:
        ecs_abort(ECS_INTERNAL_ERROR, NULL);
    }

    return read;
}

static
bool ecs_table_reader_next(
    ecs_stream_t *stream)
{
    ecs_table_reader_t *reader = &stream->reader.table;
    ecs_chunked_t *tables = stream->reader.tables;

    switch(reader->cur) {
    case EcsTableHeader:
        reader->cur = EcsTableTypeSize;

        do {
            reader->table = ecs_chunked_get(tables, ecs_table_t, reader->table_index);
            reader->columns = reader->table->columns;
            reader->table_index ++;

            /* Keep looping until a table is found that isn't filtered out */
        } while (!reader->columns);

        reader->type = reader->table->type;
        reader->type_index = 0;
        reader->total_columns = ecs_vector_count(reader->type) + 1;
        reader->column_index = 0;
        break;

    case EcsTableTypeSize:
        reader->cur = EcsTableType;
        break;

    case EcsTableType:
        reader->type_index ++;
        if (reader->type_index == ecs_vector_count(reader->type)) {
            reader->cur = EcsTableSize;
        }
        break;

    case EcsTableSize:
        reader->cur = EcsTableColumnHeader;
        break;

    case EcsTableColumnHeader:
        reader->cur = EcsTableColumnSize;
        reader->column = &reader->columns[reader->column_index];
        reader->column_size = 
            ecs_vector_count(reader->column->data) * reader->column->size;
        break;

    case EcsTableColumnSize:
        reader->cur = EcsTableColumnData;
        reader->column_data = ecs_vector_first(reader->column->data);
        reader->column_written = 0;
        break;

    case EcsTableColumnData:
        reader->column_index ++;
        if (reader->column_index == reader->total_columns) {
            reader->cur = EcsTableHeader;
            if (reader->table_index == ecs_chunked_count(tables)) {
                stream->reader.cur = EcsFooterSegment;
            }            
        } else {
            reader->cur = EcsTableColumnHeader;
        }
        break;

    default:
        ecs_abort(ECS_INTERNAL_ERROR, NULL);
    }

    return true;
}

static
size_t ecs_table_reader(
    void *buffer,
    size_t size,
    ecs_stream_t *stream)
{
    if (!size) {
        return 0;
    }

    if (size < sizeof(int32_t)) {
        return -1;
    }

    ecs_table_reader_t *reader = &stream->reader.table;
    size_t read = 0;

    if (!reader->cur) {
        reader->cur = EcsTableHeader;
    }

    switch(reader->cur) {
    case EcsTableHeader:  
        *(ecs_blob_header_kind_t*)buffer = EcsTableHeader;
        read = sizeof(ecs_blob_header_kind_t);
        ecs_table_reader_next(stream);
        break;

    case EcsTableTypeSize:  
        *(int32_t*)buffer = ecs_vector_count(reader->type);
        read = sizeof(int32_t);
        ecs_table_reader_next(stream);
        break;  

    case EcsTableType: {
        ecs_vector_params_t params = {.element_size = sizeof(ecs_entity_t)};
        *(int32_t*)buffer = *(int32_t*)ecs_vector_get(reader->type, &params, reader->type_index);
        read = sizeof(int32_t);
        ecs_table_reader_next(stream);
        break;                
    }

    case EcsTableSize:
        *(int32_t*)buffer = ecs_vector_count(reader->table->columns[0].data);
        read = sizeof(int32_t);
        ecs_table_reader_next(stream);
        break;

    case EcsTableColumnHeader:
        *(ecs_blob_header_kind_t*)buffer = EcsTableColumnHeader;
        read = sizeof(ecs_blob_header_kind_t);
        ecs_table_reader_next(stream);
        break; 

    case EcsTableColumnSize:
        *(int32_t*)buffer = reader->column_size;
        read = sizeof(ecs_blob_header_kind_t);
        ecs_table_reader_next(stream);
        break; 

    case EcsTableColumnData:
        read = reader->column_size - reader->column_written;
        if (read > size) {
            read = size;
        }

        memcpy(buffer, ECS_OFFSET(reader->column_data, reader->column_written), read);
        reader->column_written += read;

        ecs_assert(reader->column_written <= reader->column_size, ECS_INTERNAL_ERROR, NULL);

        if (reader->column_written == reader->column_size) {
            ecs_table_reader_next(stream);
        }
        break;

    default:
        ecs_abort(ECS_INTERNAL_ERROR, NULL);
    }

    return read;
}

size_t ecs_stream_read(
    void *buffer,
    size_t size,
    ecs_stream_t *stream)
{
    ecs_stream_reader_t *reader = &stream->reader;
    size_t read, total_read = 0, remaining = size;

    if (!size) {
        return 0;
    }

    ecs_assert(size >= sizeof(int32_t), ECS_INVALID_PARAMETER, NULL);

    if (reader->cur == EcsComponentSegment) {
        while ((read = ecs_component_reader(ECS_OFFSET(buffer, total_read), remaining, stream))) {
            if (read == -1) {
                break;
            }

            remaining -= read;
            total_read += read;

            if (reader->cur != EcsComponentSegment) {
                break;
            }
        }

        if (read == -1) {
            return total_read;
        }

        if (!read && remaining) {
            reader->cur = EcsTableSegment;
        }
    }

    if (reader->cur == EcsTableSegment) {
        while ((read = ecs_table_reader(ECS_OFFSET(buffer, total_read), remaining, stream))) {
            remaining -= read;
            total_read += read;

            if (reader->cur != EcsTableSegment) {
                break;
            }            
        }
    }  

    return total_read;
}