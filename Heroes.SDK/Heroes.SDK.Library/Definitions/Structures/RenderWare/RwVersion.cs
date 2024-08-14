﻿namespace Heroes.SDK.Definitions.Structures.RenderWare
{
    [Equals(DoNotAddEqualityOperators = true)]
    public struct RwVersion
    {
        /// <summary>
        /// Stores the explicit RenderWare version.
        /// It is recommended that you use the individual functions here for interacting with this value.
        /// </summary>
        public uint Version;

        /// <summary>
        /// Creates a <see cref="Heroes.SDK.Definitions.Structures.RenderWare"/> version tag.
        /// </summary>
        /// <param name="version">Sets the version. i.e. 3.5.0.1 ; The RW version would be 3.</param>
        /// <param name="major">Sets the major version. i.e. 3.5.0.1 ; The RW version would be 5.</param>
        /// <param name="minor">Sets the minor version. i.e. 3.5.0.1 ; The RW version would be 0.</param>
        /// <param name="revision">Sets the revision. i.e. 3.5.0.1 ; The RW version would be 1.</param>
        /// <param name="build">The build.</param>
        public RwVersion(uint version, uint major, uint minor, uint revision, ushort build = 0xFFFF) : this()
        {
            SetVersion(version);
            SetMajor(major);
            SetMinor(minor);
            SetRevision(revision);
            SetBuild(build);
        }

        /// <summary>
        /// Gets the RW version from the RenderWare version identifier.
        /// i.e. 3.5.0.1 ; The RW version would be 3.
        /// </summary>
        /// <returns></returns>
        public uint GetVersion()
        {
            // V is Version
            // VVJJ JJNN NNBB BBBB DDDD DDDD DDDD DDDD
            // Select only Vs, and add 3 due to version being packed with it offset.
            return (Version >> 30) + 3;
        }

        /// <summary>
        /// Retrieves the major RenderWare version from the internally stored RW version.
        /// i.e. 3.5.0.1 ; The major version would be 5.
        /// </summary>
        /// <returns></returns>
        public uint GetMajor()
        {
            // J is Major build
            // VVJJ JJNN NNBB BBBB DDDD DDDD DDDD DDDD

            // Mask the J components away and shift down.
            return (Version & 0b00111100000000000000000000000000) >> 26;
        }

        /// <summary>
        /// Retrieves the minor RenderWare version from the internally stored RW version.
        /// i.e. 3.5.0.1 ; The minor version would be 0.
        /// </summary>
        /// <returns></returns>
        public uint GetMinor()
        {
            // N is Minor build
            // VVJJ JJNN NNBB BBBB DDDD DDDD DDDD DDDD
            // 0000 0011 1100 0000 0000 0000 0000 0000

            // Mask the N components away and shift down.
            return (Version & 0b00000011110000000000000000000000) >> 22;
        }

        /// <summary>
        /// Retrieves the binary revision from the internally stored RW version.
        /// i.e. 3.5.0.1 ; The revision would be 1.
        /// </summary>
        /// <returns></returns>
        public uint GetRevision()
        {
            // B is Revision
            // VVJJ JJNN NNBB BBBB DDDD DDDD DDDD DDDD
            // 0000 0000 0011 1111 0000 0000 0000 0000

            // Mask the N components away and shift down.
            return (Version & 0b00000000001111110000000000000000) >> 16;
        }

        /// <summary>
        /// Retrieves the library build tag.
        /// This value is always visually excluded because it is literally always 0xFFFF.
        /// Generally there is not a good reason to modify it.
        /// </summary>
        /// <returns></returns>
        public ushort GetBuild()
        {
            // D is library build
            // VVJJ JJNN NNBB BBBB DDDD DDDD DDDD DDDD

            // Cast reduces it to the first 16 bytes.
            return (ushort)Version;
        }

        /// <summary>
        /// Sets the RW version in the RenderWare version identifier.
        /// i.e. 3.5.0.1 ; The RW version would be 3.
        /// Allowed range of values: 3-6 inclusive.
        /// </summary>
        /// <returns></returns>
        public void SetVersion(uint version)
        {
            // VVJJ JJNN NNBB BBBB DDDD DDDD DDDD DDDD
            // 0011 1111 1111 1111 1111 1111 1111 1111
            // Remove the current version.
            Version = Version & 0b00111111111111111111111111111111;

            // Offset the version as necessary.
            version -= 3;

            // Append the new version.
            Version = Version | (version << 30);
        }

        /// <summary>
        /// Sets the major RenderWare version in the RW Version identifier.
        /// i.e. 3.5.0.1 ; The major version would be 5.
        /// Allowed range: 0-15 inclusive.
        /// </summary>
        /// <returns></returns>
        public void SetMajor(uint major)
        {
            // J is Major build
            // VVJJ JJNN NNBB BBBB DDDD DDDD DDDD DDDD
            // 1100 0011 1111 1111 1111 1111 1111 1111

            // Remove the current major.
            Version = Version & 0b11000011111111111111111111111111;

            // Append the new major.
            Version = Version | (major << 26);
        }

        /// <summary>
        /// Seta the minor RenderWare version in the internally stored RW version.
        /// i.e. 3.5.0.1 ; The minor version would be 0.
        /// Allowed range: 0-15 inclusive.
        /// </summary>
        /// <returns></returns>
        public void SetMinor(uint minor)
        {
            // N is Minor build
            // VVJJ JJNN NNBB BBBB DDDD DDDD DDDD DDDD
            // 1111 1100 0011 1111 1111 1111 1111 1111

            // Remove the Minor build.
            Version = Version & 0b11111100001111111111111111111111;

            // Append the new minor.
            Version = Version | (minor << 22);
        }

        /// <summary>
        /// Retrieves the binary revision from the internally stored RW version.
        /// i.e. 3.5.0.1 ; The revision would be 1.
        /// Allowed range: 0-63 inclusive.
        /// </summary>
        /// <returns></returns>
        public void SetRevision(uint revision)
        {
            // B is Revision
            // VVJJ JJNN NNBB BBBB DDDD DDDD DDDD DDDD
            // 1111 1111 1100 0000 1111 1111 1111 1111

            // Remove the Revision.
            Version = Version & 0b11111111110000001111111111111111;
            Version = Version | (revision << 16);
        }

        /// <summary>
        /// Sets the library build tag.
        /// This value is always visually excluded because it is literally always 0xFFFF.
        /// Generally there is not a good reason to modify it.
        /// </summary>
        /// <returns></returns>
        public void SetBuild(ushort build)
        {
            // D is library build
            // VVJJ JJNN NNBB BBBB DDDD DDDD DDDD DDDD

            // Cast reduces it to the first 16 bytes.
            Version = Version & 0xFFFF0000;
            Version = Version | build;
        }

        /// <summary>
        /// Returns a string representing the current RenderWare version.
        /// </summary>
        /// <returns></returns>
        public string ToStringShort()
        {
            return $"{GetVersion()}.{GetMajor()}.{GetMinor()}.{GetRevision()}";
        }

        /// <summary>
        /// Returns a string representing the current RenderWare version.
        /// </summary>
        /// <returns></returns>
        public override string ToString()
        {
            return $"{GetVersion()}.{GetMajor()}.{GetMinor()}.{GetRevision()}.{GetBuild():X}";
        }
    }
}
