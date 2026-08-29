namespace Engine3DRadSpace.Graphics.Rendering;
public interface IRenderer
{
    public void Begin();
    public void Draw(MeshPartDrawInfo meshPartInfo);
    public void End();
}
