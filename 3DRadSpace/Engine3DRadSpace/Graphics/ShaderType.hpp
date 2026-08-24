#pragma once

namespace Engine3DRadSpace::Graphics
{
    /// <summary>
    /// Represents the type of a shader.
    /// </summary>
    enum class ShaderType
    {
        /// <summary>
        /// Vertex shader.
        /// </summary>
        Vertex,
        /// <summary>
        /// Fragment shader. Also known as Pixel shader.
        /// </summary>
        Fragment,
        /// <summary>
        /// Domain shader.
        /// </summary>
        Domain,
        /// <summary>
        /// Geometry shader.
        /// </summary>
        Geometry,
		/// <summary>
		/// Hull shader.
		/// </summary>
        Hull,
    };
}