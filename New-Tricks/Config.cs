using New_Tricks.Template.Configuration;
using Reloaded.Mod.Interfaces;
using Reloaded.Mod.Interfaces.Structs;
using System.ComponentModel;
using Heroes.SDK.Definitions.Enums;
using System.Runtime.InteropServices;

namespace New_Tricks.Configuration
{

    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    public struct ConfigData
    {
        [MarshalAs(UnmanagedType.I1)] public bool SonkSpinDash;
        [MarshalAs(UnmanagedType.I1)] public bool ShadowSpinDash;
        [MarshalAs(UnmanagedType.I1)] public bool AmySpinDash;
        [MarshalAs(UnmanagedType.I1)] public bool BetterProp;
        [MarshalAs(UnmanagedType.I1)] public bool AmyTornadoTweaks;
        [MarshalAs(UnmanagedType.I1)] public bool EspioSpinDash;
        [MarshalAs(UnmanagedType.I1)] public bool EspioTornadoTweaks;
        [MarshalAs(UnmanagedType.I1)] public bool FlightTweaks;
        [MarshalAs(UnmanagedType.I1)] public bool IncreaseSpeedCap;
        [MarshalAs(UnmanagedType.I1)] public bool CheeseTweaks;
        [MarshalAs(UnmanagedType.I1)] public bool WidePowerTweaks;
        [MarshalAs(UnmanagedType.I1)] public bool TriangleDiveTweaks;
    }


    public static class ConfigV
    {
        static public Config _modConfig;

        public static bool isSpinDashAllowed(Character curChar)
        {
            if (_modConfig != null)
            {
                switch (curChar)
                {
                    case Character.Sonic:
                        return _modConfig.SonkSpinDash;
                    case Character.Shadow:
                        return _modConfig.ShadowSpinDash;
                    case Character.Amy:
                        return _modConfig.AmySpinDash;
                    case Character.Espio:
                        return _modConfig.EspioSpinDash;
                }
            }


            return false;
        }

        public static bool isSpinDashEnabledForAtLeastAPlayer()
        {
            if (_modConfig != null)
            {
                for (byte i = 0; i < (byte)Character.Charmy + 1; i++)
                {
                    if (isSpinDashAllowed((Character)i))
                        return true;
                }
            }

            return false;
        }
    }


    public class Config : Configurable<Config>
    {
        public ConfigData config = new();

        [DllImport("New_TricksC.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetConfigData(ConfigData data);

        [DllImport("New_TricksC.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern ConfigData GetConfig();



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
            config.SonkSpinDash = SonkSpinDash;
            config.ShadowSpinDash = ShadowSpinDash;
            config.AmySpinDash = AmySpinDash;
            config.BetterProp = BetterProp;
            config.AmyTornadoTweaks = AmyTornadoTweaks;
            config.EspioSpinDash = EspioSpinDash;
            config.EspioTornadoTweaks = EspioTornadoTweaks;
            config.FlightTweaks = FlightTweaks;
            config.IncreaseSpeedCap = IncreaseSpeedCap;
            config.CheeseTweaks = CheeseTweaks;
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
