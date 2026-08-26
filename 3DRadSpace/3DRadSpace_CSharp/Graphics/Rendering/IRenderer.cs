namespace Engine3DRadSpace.Graphics.Rendering;
public interface IRenderer
{
    public void Begin();
    public void Draw(ModelMeshPart meshPart, in MaterialDescriptor descriptor);
    public void End();
}
