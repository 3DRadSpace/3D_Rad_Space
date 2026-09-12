using Engine3DRadSpace.Graphics;

namespace Engine3DRadSpace.Objects;

public interface IObject : IInitializable, IUpdateable, ILoadable, IPtrWrapper
{
	   public string Name { get; set; }
	   public bool Enabled { get; set; }
	   public bool Visible { get; set; }

	   public void Enable();
	   public void Disable();
	   public bool Switch();

	   public void Show();
	   public void Hide();
	   public bool SwitchVisibility();

	   Reflection.UUID UUID { get; }
	   IGame Game { get; }
	   IGraphicsDevice GraphicsDevice { get; }
	   IGizmo Gizmo { get; }
	   ObjectCollection Children { get; }

	   IObject GetChild(int idx);
	   int GetChildrenCount();
	   IObject Parent { get; set; }
}
