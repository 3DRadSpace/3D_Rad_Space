using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace Lib3DRadSpace_DX
{
    internal class MollerTrumbore
    {
		internal static Vector3? RayMeshCollision(Ray r, Model m, Matrix translation)
		{
			for(int i = 0; i < m.Meshes.Count; i++)
			{
				for(int j = 0; j < m.Meshes[i].MeshParts.Count; j++)
				{
					Vector3[] verts = new Vector3[m.Meshes[i].MeshParts[j].NumVertices];
					m.Meshes[i].MeshParts[j].VertexBuffer.GetData(m.Meshes[i].MeshParts[j].VertexOffset + (m.Meshes[i].MeshParts[j].VertexOffset * m.Meshes[i].MeshParts[j].VertexBuffer.VertexDeclaration.VertexStride),
						verts, 0, m.Meshes[i].MeshParts[j].NumVertices, m.Meshes[i].MeshParts[j].VertexBuffer.VertexDeclaration.VertexStride);

					short[] indicies = new short[m.Meshes[i].MeshParts[j].IndexBuffer.IndexCount];
					m.Meshes[i].MeshParts[j].IndexBuffer.GetData(m.Meshes[i].MeshParts[j].StartIndex * 2, indicies, 0, m.Meshes[i].MeshParts[j].PrimitiveCount * 3);

					for(int k = 0; k < verts.Length; k++)
					{
						verts[k] = Vector3.Transform(verts[k], translation);
					}

					for(int k = 0; k < indicies.Length; k += 3)
					{
						Triangle tri = new Triangle(verts[indicies[k]], verts[indicies[k + 1]], verts[indicies[k + 2]]);
						if(MollerTrumboreIntersection(r, tri, out Vector3? intersection)) return intersection;
					}
				}
			}
			return null;
		}
		/// <summary>
		///  Ray-Triangle intersection algorithm
		///  Source : https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
		/// </summary>
		/// <param name="r"></param>
		/// <param name="tri"></param>
		/// <param name="intersectionP"></param>
		/// <returns></returns>
		internal static bool MollerTrumboreIntersection(Ray r, Triangle tri, out Vector3? intersectionP)
		{
			const float EPSILON = 0.0000001f;
			Vector3 vertex0 = tri.vertex0;
			Vector3 vertex1 = tri.vertex1;
			Vector3 vertex2 = tri.vertex2;
			Vector3 edge1, edge2, h, s, q;
			float a, f, u, v;
			edge1 = vertex1 - vertex0;
			edge2 = vertex2 - vertex0;
			h = Vector3.Cross(r.Direction, edge2);
			a = Vector3.Dot(edge1, h);
			if(a > -EPSILON && a < EPSILON)
			{
				intersectionP = null;
				return false;    // This ray is parallel to this triangle.
			}
			f = 1.0f / a;
			s = r.Position - vertex0;
			u = f * Vector3.Dot(s, h);
			if(u < 0.0 || u > 1.0)
			{
				intersectionP = null;
				return false;
			}
			q = Vector3.Cross(s, edge1);
			v = f * Vector3.Dot(r.Direction, q);
			if(v < 0.0 || u + v > 1.0)
			{
				intersectionP = null;
				return false;
			}
			// At this stage we can compute t to find out where the intersection point is on the line.
			float t = f * Vector3.Dot(edge2, q);
			if(t > EPSILON) // ray intersection
			{
				intersectionP = r.Position + r.Direction * t;
				return true;
			}
			else // This means that there is a line intersection but not a ray intersection.
			{
				intersectionP = null;
				return false;
			}
		}
		internal struct Triangle
		{
			public Vector3 vertex0;
			public Vector3 vertex1;
			public Vector3 vertex2;
			public Triangle(Vector3 a, Vector3 b, Vector3 c)
			{
				vertex0 = a;
				vertex1 = b;
				vertex2 = c;
			}
		}
	}
}
