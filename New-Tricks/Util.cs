using Reloaded.Hooks.Definitions;
using Reloaded.Hooks.Definitions.X86;
using Reloaded.Memory;
using Reloaded.Memory.Interfaces;


public static class Util
{
    public static void WriteNop(nuint address, ushort count)
    {
        byte[] nopBytes = new byte[count];
        for (int i = 0; i < nopBytes.Length; i++)
        {
            nopBytes[i] = (byte)0x90;
        }
        Memory.Instance.SafeWrite(address, nopBytes);
    }

    public static void WriteData(nuint address, Span<byte> byte_)
    {
        Memory.Instance.SafeWrite(address, byte_);
    }

    public static byte[] nopFunc = new byte[] { 0x90, 0x90, 0x90, 0x90, 0x90 };
}

