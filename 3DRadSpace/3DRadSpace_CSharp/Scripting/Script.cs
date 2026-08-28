using Engine3DRadSpace.Objects;

namespace Engine3DRadSpace.Scripting
{
    public class Script : IScript
    {
        public IObject Object { get; internal set; }

        public Script() 
        {
        }

        public virtual void Start()
        {
        }

        public virtual void Update()
        {
        }

        public virtual void End()
        {

        }
    }
}
