using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _3DRadSpaceDll
{
    public class Camera : GameObject
    {
        public Camera()
        {
            Name = "Camera";
            Enabled = false;
            _pos = Vector3.Zero;
            _rot = Vector3.UnitZ;
            _fov = MathHelper.ToRadians(45);
            _far = 500f;
            _near = 0.01f;
            _aspect_ratio = 600 / 480f;
            _up = Vector3.Up;
            RecalculateMatrices();
        }
        /// <summary>
        /// View matrix
        /// </summary>
        public Matrix View;
        /// <summary>
        /// Projection
        /// </summary>
        public Matrix Projection;
        /// <summary>
        /// Position of the camera object.
        /// </summary>
        public new Vector3 Position
        {
            get
            {
                return _pos;
            }
            set
            {
                View = Matrix.CreateLookAt(value, value + _rot, _up);
                _pos = value;
            }
        }
        /// <summary>
        /// Describes a normalized vector describing the 3D rotation in unit-angles
        /// </summary>
        public new Vector3 Rotation
        {
            get
            {
                return _rot;
            }
            set
            {
                View = Matrix.CreateLookAt(_pos, value, _up);
            }
        }
        Vector3 _pos;
        Vector3 _rot;
        /// <summary>
        /// The Model used in the Editor
        /// </summary>
        public static Model EditorModel;
        /// <summary>
        /// Describes the camera's up direction as a unit vector.
        /// </summary>
        public Vector3 Up
        {
            get
            {
                return _up;
            }
            set
            {
                View = Matrix.CreateLookAt(_pos, _rot, value);
                _up = value;
            }
        }
        Vector3 _up;
        /// <summary>
        /// Field of view in radians.
        /// </summary>
        public float FOV
        {
            get
            {
                return _fov;
            }
            set
            {
                Projection = Matrix.CreatePerspectiveFieldOfView(value, _aspect_ratio, _near, _far);
                _fov = value;
            }
        }
        float _fov;
        /// <summary>
        /// Aspect ratio defined as x/y px .
        /// </summary>
        public float AspectRatio
        {
            get
            {
                return _aspect_ratio;
            }
            set
            {
                Projection = Matrix.CreatePerspectiveFieldOfView(_fov, value, _near, _far);
                _aspect_ratio = value;
            }
        }
        float _aspect_ratio;
        /// <summary>
        /// Minimum drawing distance
        /// </summary>
        public float NearDrawDistance
        {
            get
            {
                return _near;
            }
            set
            {
                Projection = Matrix.CreatePerspectiveFieldOfView(_fov, _aspect_ratio, value,_far);
                _near = value;
            }
        }
        float _near;
        /// <summary>
        /// Maximum draw distance
        /// </summary>
        public float FarDrawDistance
        {
            get
            {
                return _far;
            }
            set
            {
                Projection = Matrix.CreatePerspectiveFieldOfView(_fov, _aspect_ratio, _near, value);
                _far = value;
            }
        }
        float _far;
        public Camera(string name,bool enabled,Vector3 pos,Vector3 rot,Vector3 up,float fov,float aspect_ratio,float near,float far)
        {
            Vector3 n = Vector3.Transform(Vector3.UnitZ, Matrix.CreateFromYawPitchRoll(rot.Y, rot.X, rot.Y));
            View = Matrix.CreateLookAt(pos, pos + n, up);
            Projection = Matrix.CreatePerspectiveFieldOfView(fov, aspect_ratio, near, far);
            Name = name;
            Enabled = enabled;
            _pos = pos;
            _rot = n;
            _up = up;
            _fov = fov;
            _aspect_ratio = aspect_ratio;
            _far = far;
            _near = near;
        }
        public BoundingFrustum Frustum
        {
            get
            {
                return new BoundingFrustum(View * Projection);
            }
        }
        public void RecalculateMatrices()
        {
            View = Matrix.CreateLookAt(_pos, _pos + _rot,_up);
            Projection = Matrix.CreatePerspectiveFieldOfView(_fov, _aspect_ratio, _near, _far);
        }
    }
}
