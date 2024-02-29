#include "triangle_mesh_geometry.hpp"
#include "objects/triangle_mesh.hpp"

namespace RT_ISICG
{
	TriangleMeshGeometry::TriangleMeshGeometry( const unsigned int p_v0,
												const unsigned int p_v1,
												const unsigned int p_v2,
												MeshTriangle *	   p_refMesh )
		: _v0( p_v0 ), _v1( p_v1 ), _v2( p_v2 ), _refMesh( p_refMesh )
	{
		_faceNormal = glm::normalize( glm::cross( _refMesh->_vertices[ p_v1 ] - _refMesh->_vertices[ p_v0 ],
												  _refMesh->_vertices[ p_v2 ] - _refMesh->_vertices[ p_v0 ] ) );
	}

	bool TriangleMeshGeometry::intersect( const Ray & p_ray, float & p_t ) const
	{
		const Vec3f & o	 = p_ray.getOrigin();
		const Vec3f & d	 = p_ray.getDirection();
		const Vec3f & v0 = _refMesh->_vertices[ _v0 ];
		const Vec3f & v1 = _refMesh->_vertices[ _v1 ];
		const Vec3f & v2 = _refMesh->_vertices[ _v2 ];

		constexpr float epsilon = std::numeric_limits<float>::epsilon();

		Vec3f edge1, edge2;
		edge1 = v1 - v0;
		edge2 = v2 - v0;

		Vec3f rayEdge2 = glm::cross( d, edge2 );
		float det	   = glm::dot( edge1, rayEdge2 );
		if ( det > -epsilon && det < epsilon ) return false;

		float invDet = 1.f / det;
		Vec3f s		 = o - v0;
		float u		 = invDet * glm::dot( s, rayEdge2 );

		if ( u < 0 || u > 1 ) return false;

		Vec3f sCrossEdge1 = glm::cross( s, edge1 );
		float v			  = invDet * glm::dot( d, sCrossEdge1 );

		if ( v < 0 || u + v > 1 ) return false;

		float t = invDet * glm::dot( edge2, sCrossEdge1 );

		if ( t > epsilon )
		{
			p_t = t;
			//uv	= Vec2f( u, v );
			return true;
		}

		else
		{
			p_t = -1.f;
			return false;
		}
	}


} // namespace RT_ISICG
