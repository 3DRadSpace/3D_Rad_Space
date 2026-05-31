#pragma once

/// All headers[1] are included here. To be added preferably in a precompiled header for end-user projects.
/// Not to be included inside the engine itself [2].
/// [1] - Except:
/// - Headers from Internal, they're only meant to be used by the engine itself.
/// - Legacy header, it exports C functions to the AngelScript interface.
///   Including it would also cause a circular depedency, since Legacy.hpp includes this header.
/// [2] - As already specified, this is meant for projects that use the engine as a framework.

//Header files ordered alphabetically and by namespaces.


//Engine3DRadSpace
#include "Core/Libs.hpp"
#include "Core\IDrawable2D.hpp"
#include "Core\IDrawable3D.hpp"
#include "Core\IInitializable.hpp"
#include "Core\ILoadable.hpp"
#include "Core\IUpdateable.hpp"
#include "Core\IGame.hpp"

//Engine3DRadSpace::Audio
#include "Audio\AudioBuffer.hpp"
#include "Audio\AudioEngine.hpp"
#include "Audio\AudioError.hpp"
#include "Audio\AudioSource.hpp"
#include "Audio\Listener.hpp"
#include "Audio\Sound.hpp"
#include "Audio\SoundInstance.hpp"
#include "Audio\SoundState.hpp"

//Engine3DRadSpace::Content
#include "Content\AssetID.hpp"
#include "Content\ContentManager.hpp"
#include "Content\IAsset.hpp"

//Engine3DRadSpace::Content::Assets
#include "Content\Assets\SkyboxAsset.hpp"

//Engine3DRadSpace::Graphics
#include "Graphics\IBlendState.hpp"
#include "Graphics\BufferUsage.hpp"
#include "Graphics\IDepthStencilBuffer.hpp"
#include "Graphics\IDepthStencilState.hpp"
#include "Graphics\FlipMode.hpp"
#include "Graphics\Font.hpp"
#include "Graphics\Glyph.hpp"
#include "Graphics\IIndexBuffer.hpp"
#include "Graphics\IShader.hpp"
#include "Graphics\Model3D.hpp"
#include "Graphics\ModelMesh.hpp"
#include "Graphics\ModelMeshPart.hpp"
#include "Graphics\PixelFormat.hpp"
#include "Graphics\IRasterizerState.hpp"
#include "Graphics\IRenderTarget.hpp"
#include "Graphics\ISamplerState.hpp"
#include "Graphics\ShaderCompilationError.hpp"
#include "Graphics\ShaderFeatureLevel.hpp"
#include "Graphics\SpriteBatch.hpp"
#include "Graphics\ITexture2D.hpp"
#include "Graphics\IVertexBuffer.hpp"
#include "Graphics\VertexDeclarations.hpp"
#include "Graphics\VertexTopology.hpp"
#include "Graphics\Viewport.hpp"

//Engine3DRadSpace::Graphics::Primitives
#include "Graphics\Primitives\Arrow.hpp"
#include "Graphics\Primitives\Box.hpp"
#include "Graphics\Primitives\CilindricalBillboard.hpp"
#include "Graphics\Primitives\Circle.hpp"
#include "Graphics\Primitives\CubeMapSkybox.hpp"
#include "Graphics\Primitives\IPrimitive.hpp"
#include "Graphics\Primitives\LineList.hpp"
#include "Graphics\Primitives\LineStrip.hpp"
#include "Graphics\Primitives\Plane.hpp"
#include "Graphics\Primitives\Sphere.hpp"

//Engine3DRadSpace::Graphics::Rendering
#include "Graphics\Rendering\ForwardRenderer.hpp"
#include "Graphics\Rendering\IRenderer.hpp"
#include "Graphics\Rendering\LinearPixelFogEffect.hpp"
#include "Graphics\Rendering\PostProcessCollection.hpp"
#include "Graphics\Rendering\PostProcessEffect.hpp"

//Engine3DRadSpace::Input
#include "Input\ButtonState.hpp"
#include "Input\Key.hpp"
#include "Input\Keyboard.hpp"
#include "Input\KeyState.hpp"
#include "Input\Mouse.hpp"

//Engine3DRadSpace::Logging
#include "Logging\Exception.hpp"
#include "Logging\Message.hpp"
#include "Logging\AssetLoadingError.hpp"
#include "Logging\Warning.hpp"

//Engine3DRadSpace::Math
#include "Math\BoundingBox.hpp"
#include "Math\BoundingPlane.hpp"
#include "Math\BoundingSphere.hpp"
#include "Math\Math.hpp"
#include "Math\Matrix3x3.hpp"
#include "Math\Matrix4x4.hpp"
#include "Math\Point.hpp"
#include "Math\Quaternion.hpp"
#include "Math\Ray.hpp"
#include "Math\Rectangle.hpp"
#include "Math\Triangle.hpp"
#include "Math\Vector2.hpp"
#include "Math\Vector3.hpp"
#include "Math\Vector4.hpp"

//Engine3DRadSpace::Objects
#include "Objects\ICamera.hpp"
#include "Objects\IObject.hpp"
#include "Objects\IObject2D.hpp"
#include "Objects\IObject3D.hpp"
#include "Objects\ObjectList.hpp"
#include "Objects\ObjectType.hpp"

//Engine3DRadSpace::Objects::Impl
#include "Objects\Impl\Skinmesh.hpp"
#include "Objects\Impl\Skybox.hpp"
#include "Objects\Impl\SkyColor.hpp"
#include "Objects\Impl\SoundEffect.hpp"
#include "Objects\Impl\SoundSource.hpp"
#include "Objects\Impl\Sprite.hpp"
#include "Objects\Impl\TextPrint.hpp"
#include "Objects\Impl\Camera.hpp"
#include "Objects\Impl\Counter.hpp"
#include "Objects\Impl\Empty.hpp"
#include "Objects\Impl\ExitFade.hpp"
#include "Objects\Impl\Fog.hpp"

//Engine3DRadSpace::Native
#include "Native\LibraryLoader.hpp"
#include "Native\Window.hpp"

//Engine3DRadSpace::Physics
#include "Physics\ICollider.hpp"
#include "Physics\IPhysicsEngine.hpp"
#include "Physics\PhysicsSettings.hpp"
//Engine3DRadSpace::Physics::Objects
#include "Physics\Objects\GForce.hpp"
#include "Physics\Objects\IPhysicsObject.hpp"

//Engine3DRadSpace::Plugins
#include "Plugins\CustomObject.hpp"
#include "Plugins\EditorPlugin.hpp"
#include "Plugins\PluginInfo.hpp"

//Engine3DRadSpace::Projects
#include "Projects\Serialization.hpp"