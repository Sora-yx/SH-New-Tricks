using Reloaded.Hooks.Definitions;
using Reloaded.Hooks.Definitions.X86;
using Reloaded.Memory;
using Reloaded.Memory.Interfaces;
using System.Diagnostics;
using System.Diagnostics.CodeAnalysis;
using System.Runtime.InteropServices;


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

    public static void WriteData(nuint address, byte byte_)
    {
        byte[] monoByte = { byte_ };
        Memory.Instance.SafeWrite(address, monoByte);
    }

    public static void WriteDataInArray<T>(nuint address, T item, ushort index)
    {
        if (item is not null)
            Memory.Instance.WriteWithMarshalling(address + (nuint)(Marshal.SizeOf(typeof(T)) * index), item);
    }

    public static byte[] nopFunc = new byte[] { 0x90, 0x90, 0x90, 0x90, 0x90 };
}

