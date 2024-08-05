using Reloaded.Hooks.Definitions;
using Reloaded.Hooks.Definitions.X86;
using Reloaded.Memory;
using Reloaded.Memory.Interfaces;


public static class Util
{


    public static void WriteData(nuint address, Span<byte> byte_)
    {
        Memory.Instance.SafeWrite(address, byte_);
    }

    public static byte[] nopFunc = new byte[] { 0x90, 0x90, 0x90, 0x90, 0x90 };
}

