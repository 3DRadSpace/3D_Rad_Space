using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using BEPUutilities;
using BEPUphysics.BroadPhaseEntries;
using Microsoft.Xna.Framework.Graphics;

namespace Lib3DRadSpace_DX
{
    /*
     * Physics related helper functions
     */

    static class BEPU2XNA
    {
        public static Vector3 CvVec(Microsoft.Xna.Framework.Vector3 v)
        {
            return new Vector3(v.X, v.Y, v.Z);
        }
        public static Vector3[] CvVec(Microsoft.Xna.Framework.Vector3[] v)
        {
            Vector3[] r = new Vector3[v.Length];
            for(int i =0; i < v.Length;i++)
            {
                r[i] = CvVec(v[i]);
            }
            return r;
        }
        public static StaticMesh CreateCollisionMeshPart(ModelMeshPart part)
        {
            Vector3[] verts = new Vector3[part.NumVertices];
            part.VertexBuffer.GetData<Vector3>(part.VertexOffset + (part.VertexOffset * part.VertexBuffer.VertexDeclaration.VertexStride),
                verts, 0, part.NumVertices, part.VertexBuffer.VertexDeclaration.VertexStride);

            short[] ind = new short[part.IndexBuffer.IndexCount];
            part.IndexBuffer.GetData(part.StartIndex * 2, ind, 0, part.PrimitiveCount * 3);

            int[] rind = new int[part.IndexBuffer.IndexCount];
            for(int i = 0; i < part.IndexBuffer.IndexCount; i++) rind[i] = ind[i];

            return new StaticMesh(verts, rind);
        }
        public static StaticMesh[] GenerateCollisionMesh(Model model)
        {
            int sum = 0;
            for(int i = 0; i < model.Meshes.Count; i++)
            {
                for(int j = 0; j < model.Meshes[i].MeshParts.Count; j++) sum++;
            }

            StaticMesh[] r = new StaticMesh[sum];

            sum = 0;
            for(int i = 0; i < model.Meshes.Count; i++)
            {
                for(int j = 0; j < model.Meshes[i].MeshParts.Count; j++)
                {
                    r[sum] = CreateCollisionMeshPart(model.Meshes[i].MeshParts[j]);
                    sum++;
                }
            }
            return r;
        }
    }
}
