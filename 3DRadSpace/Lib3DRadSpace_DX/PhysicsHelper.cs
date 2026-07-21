using BEPUutilities;
using BEPUphysics.BroadPhaseEntries;
using Microsoft.Xna.Framework.Graphics;

using XNAVector3 = Microsoft.Xna.Framework.Vector3;
using System;

namespace Lib3DRadSpace_DX
{
    /*
     * Physics related helper functions
     */

    static internal class BEPU2XNA
    {
        internal static Vector3 CvVec(XNAVector3 v)
        {
            return new Vector3(v.X, v.Y, v.Z);
        }
        internal static Vector3[] CvVec(XNAVector3[] v)
        {
            Vector3[] r = new Vector3[v.Length];
            for(int i =0; i < v.Length;i++)
            {
                r[i] = CvVec(v[i]);
            }
            return r;
        }
        internal static StaticMesh CreateCollisionMeshPart(ModelMeshPart part)
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
        internal static StaticMesh[] GenerateCollisionMesh(Model model)
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
        internal static XNAVector3 XNAVector(Vector3 v)
        {
            return new XNAVector3(v.X, v.Y, v.Z);
        }
        internal static Vector3 BEPUVector(XNAVector3 v)
        {
            return new Vector3(v.X, v.Y, v.Z);
        }

        internal static Quaternion BEPUQuaternion(Microsoft.Xna.Framework.Quaternion quaternion)
        {
            return new Quaternion(quaternion.X,quaternion.Y,quaternion.Z,quaternion.W);
        }
    }
}
