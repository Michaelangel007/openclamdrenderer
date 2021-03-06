#ifndef INCLUDED_H_OBJ_G_DESCRIPTOR
#define INCLUDED_H_OBJ_G_DESCRIPTOR
#include <CL/CL.h>

#define MIP_LEVELS 4

///this is gpu side
struct obj_g_descriptor
{
    cl_float4 world_pos; ///w is blank
    cl_float4 world_rot; ///w is blank
    cl_uint start; ///start triangle num
    cl_uint tri_num; ///length of triangles (ie start; i < start + tri_num; i++)
    cl_uint tid; ///texture id
    cl_uint mip_level_ids[MIP_LEVELS];
    cl_uint has_bump;
    cl_uint cumulative_bump;
    ///add in a type here for shaders?
};

#endif // INCLUDED_H_OBJ_G_DESCRIPTOR
