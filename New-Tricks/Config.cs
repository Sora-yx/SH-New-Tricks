using New_Tricks.Template.Configuration;
using System.ComponentModel;
using System.Runtime.InteropServices;

namespace New_Tricks.Configuration
{

    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    public struct ConfigData
    {
        [MarshalAs(UnmanagedType.I1)] public bool UseDPadForFormSwap;
        [MarshalAs(UnmanagedType.I1)] public bool SonkSpinDash;
        [MarshalAs(UnmanagedType.I1)] public bool ShadowSpinDash;
        [MarshalAs(UnmanagedType.I1)] public bool AmySpinDash;
        [MarshalAs(UnmanagedType.I1)] public bool BetterProp;
        [MarshalAs(UnmanagedType.I1)] public bool AmyTornadoTweaks;
        [MarshalAs(UnmanagedType.I1)] public bool AmyBird;
        [MarshalAs(UnmanagedType.I1)] public bool EspioSpinDash;
        [MarshalAs(UnmanagedType.I1)] public bool EspioTornadoTweaks;
        [MarshalAs(UnmanagedType.I1)] public bool FlightTweaks;
        [MarshalAs(UnmanagedType.I1)] public bool IncreaseSpeedCap;
        [MarshalAs(UnmanagedType.I1)] public bool CheeseTweaks;
        [MarshalAs(UnmanagedType.I1)] public bool EnableChocola;
        [MarshalAs(UnmanagedType.I1)] public bool WidePowerTweaks;
        [MarshalAs(UnmanagedType.I1)] public bool TriangleDiveTweaks;
    }


    public static class ConfigV
    {
        static public Config _modConfig;
    }


    public class Config : Configurable<Config>
    {
        public ConfigData config = new();

        [DllImport("New_TricksC.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetConfigData(ConfigData data);

        [DllImport("New_TricksC.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern ConfigData GetConfig();


        [Category("General")]
        [DisplayName("Use d-pad for formation changes")]
        [Description("Make d-pad left or right swap team member, this is needed for some custom moves that use Y and B." +
            "\n Note: For keyboard users, use the Controller Hook method to set a key for d-pad." +
            "\n\nWARNING, DISABLING THIS WILL PREVENT SOME CUSTOM MOVES TO WORK.")]
        [DefaultValue(true)]
        public bool UseDPadForFormSwap { get; set; } = true;

        [Category("Sonic")]
        [DisplayName("SA1 Spin Dash")]
        [Description("Replace Rocket Accel with SA1 Spin Dash for Sonic, the Spin Dash goes faster as the Speed Level raise.")]
        [DefaultValue(true)]
        public bool SonkSpinDash { get; set; } = true;

        [Category("Shadow")]
        [DisplayName("SA1 Spin Dash")]
        [Description("Replace Rocket Accel with SA1Spin Dash for Shadow, the Spin Dash goes faster as the Speed Level raise.")]
        [DefaultValue(true)]
        public bool ShadowSpinDash { get; set; } = true;

        [Category("Amy")]
        [DisplayName("SA1 Spin Dash")]
        [Description("Replace Rocket Accel with SA1 Spin Dash for Amy, the Spin Dash goes faster as the Speed Level raise.")]
        [DefaultValue(true)]
        public bool AmySpinDash { get; set; } = true;

        [Category("Amy")]
        [DisplayName("Propeller Tweaks")]
        [Description("Make Amy Propeller moves faster and increase its duration depending on the Speed Level. (Hold Jump to use it.)")]
        [DefaultValue(true)]
        public bool BetterProp { get; set; } = true;

        [Category("Amy")]
        [DisplayName("Tornado Tweaks")]
        [Description("Make Amy's Tornado faster, also remove momentum restriction and camera zoom.")]
        [DefaultValue(true)]
        public bool AmyTornadoTweaks { get; set; } = true;

        [Category("Amy")]
        [DisplayName("Enable Bird")]
        [Description("Bring back the SA1 Bird that follow Amy for maximum nostalgia.")]
        [DefaultValue(true)]

        public bool AmyBird { get; set; } = true;

        [Category("Espio")]
        [DisplayName("SA1 Spin Dash")]
        [Description("Replace Rocket Accel with SA1 Spin Dash for Espio, the Spin Dash goes faster as the Speed Level raise.")]
        [DefaultValue(true)]
        public bool EspioSpinDash { get; set; } = true;

        [Category("Espio")]
        [DisplayName("Tornado Tweaks")]
        [Description("Make Espio's Tornado faster, also remove momentum restriction.")]
        [DefaultValue(true)]
        public bool EspioTornadoTweaks { get; set; } = true;


        [Category("Fly Characters")]
        [DisplayName("Flight Tweaks")]
        [Description("Increase Flight duration and speed, the values ​​rise as the flight level increase. This also keeps momentum when flight end.")]
        [DefaultValue(true)]
        public bool FlightTweaks { get; set; } = true;

        [Category("Fly Characters")]
        [DisplayName("Increase Vertical Speed Cap")]
        [Description("Increase the flying vertical speed cap, allowing you to go higher.")]
        [DefaultValue(true)]
        public bool IncreaseSpeedCap { get; set; } = true;

        [Category("Cream")]
        [DisplayName("Cheese Tweaks")]
        [Description("Make Cheese attack faster, allow Cream to move at the same time.")]
        [DefaultValue(true)]
        public bool CheeseTweaks { get; set; } = true;

        [Category("Cream")]
        [DisplayName("Enable Chocola")]
        [Description("Make Chocola show up with Cheese after completing Team Rose.")]
        [DefaultValue(true)]
        public bool EnableChocola { get; set; } = true;

        [Category("Power Characters")]
        [DisplayName("Wide Power Attack Tweaks")]
        [Description("Allow Power characters to move during the Wide Power Attack.")]
        [DefaultValue(true)]
        public bool WidePowerTweaks { get; set; } = true;

        [Category("Power Characters")]
        [DisplayName("Triangle Dive Tweaks")]
        [Description("Allow to use Triangle Dive while falling.")]
        [DefaultValue(true)]
        public bool TriangleDiveTweaks { get; set; } = true;



        public void InitCppConfig()
        {
            config.UseDPadForFormSwap = UseDPadForFormSwap;
            config.SonkSpinDash = SonkSpinDash;
            config.ShadowSpinDash = ShadowSpinDash;
            config.AmySpinDash = AmySpinDash;
            config.BetterProp = BetterProp;
            config.AmyTornadoTweaks = AmyTornadoTweaks;
            config.AmyBird = AmyBird;
            config.EspioSpinDash = EspioSpinDash;
            config.EspioTornadoTweaks = EspioTornadoTweaks;
            config.FlightTweaks = FlightTweaks;
            config.IncreaseSpeedCap = IncreaseSpeedCap;
            config.CheeseTweaks = CheeseTweaks;
            config.EnableChocola = EnableChocola;
            config.WidePowerTweaks = WidePowerTweaks;
            config.TriangleDiveTweaks = TriangleDiveTweaks;  
            SetConfigData(config);
        }

    }

    /// <summary>
    /// Allows you to override certain aspects of the configuration creation process (e.g. create multiple configurations).
    /// Override elements in <see cref="ConfiguratorMixinBase"/> for finer control.
    /// </summary>
    public class ConfiguratorMixin : ConfiguratorMixinBase
    {
        // 
    }
}
