using New_Tricks.Template.Configuration;
using Reloaded.Mod.Interfaces;
using Reloaded.Mod.Interfaces.Structs;
using System.ComponentModel;
using Heroes.SDK.Definitions.Enums;

namespace New_Tricks.Configuration
{

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
        /*
            User Properties:
                - Please put all of your configurable properties here.
    
            By default, configuration saves as "Config.json" in mod user config folder.    
            Need more config files/classes? See Configuration.cs
    
            Available Attributes:
            - Category
            - DisplayName
            - Description
            - DefaultValue

            // Technically Supported but not Useful
            - Browsable
            - Localizable

            The `DefaultValue` attribute is used as part of the `Reset` button in Reloaded-Launcher.
        */

        [Category("Sonic")]
        [DisplayName("SA1 Spin Dash")]
        [Description("Replace Rocket Accel with Adventure Spin Dash for Sonic, the Spin Dash goes faster as the Speed Level raise.")]
        [DefaultValue(true)]
        public bool SonkSpinDash { get; set; } = true;

        [Category("Shadow")]
        [DisplayName("SA1 Spin Dash")]
        [Description("Replace Rocket Accel with Adventure Spin Dash for Shadow, the Spin Dash goes faster as the Speed Level raise.")]
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

        [Category("Power Characters")]
        [DisplayName("Wide Power Attack Tweaks")]
        [Description("Allow Power characters to move during the Wide Power Attack.")]
        [DefaultValue(true)]
        public bool WidePowerTweaks { get; set; } = true;

        [Category("Power Characters")]
        [DisplayName("Triangle Dive Tweaks")]
        [Description("Increase Triangle Dive speed, the values rises as the power level increase, this also allow to use it while falling.")]
        [DefaultValue(true)]
        public bool TriangleDiveTweaks { get; set; } = true;


        /*[DisplayName("String")]
        [Description("This is a string.")]
        [DefaultValue("Default Name")]
        public string String { get; set; } = "Default Name";

        [DisplayName("Int")]
        [Description("This is an int.")]
        [DefaultValue(42)]
        public int Integer { get; set; } = 42;

        [DisplayName("Bool")]
        [Description("This is a bool.")]
        [DefaultValue(true)]
        public bool Boolean { get; set; } = true;

        [DisplayName("Float")]
        [Description("This is a floating point number.")]
        [DefaultValue(6.987654F)]
        public float Float { get; set; } = 6.987654F;

        [DisplayName("Enum")]
        [Description("This is an enumerable.")]
        [DefaultValue(SampleEnum.ILoveIt)]
        public SampleEnum Reloaded { get; set; } = SampleEnum.ILoveIt;

        public enum SampleEnum
        {
            NoOpinion,
            Sucks,
            IsMediocre,
            IsOk,
            IsCool,
            ILoveIt
        }

        [DisplayName("Int Slider")]
        [Description("This is a int that uses a slider control similar to a volume control slider.")]
        [DefaultValue(100)]
        [SliderControlParams(
            minimum: 0.0,
            maximum: 100.0,
            smallChange: 1.0,
            largeChange: 10.0,
            tickFrequency: 10,
            isSnapToTickEnabled: false,
            tickPlacement: SliderControlTickPlacement.BottomRight,
            showTextField: true,
            isTextFieldEditable: true,
            textValidationRegex: "\\d{1-3}")]
        public int IntSlider { get; set; } = 100;

        [DisplayName("Double Slider")]
        [Description("This is a double that uses a slider control without any frills.")]
        [DefaultValue(0.5)]
        [SliderControlParams(minimum: 0.0, maximum: 1.0)]
        public double DoubleSlider { get; set; } = 0.5;

        [DisplayName("File Picker")]
        [Description("This is a sample file picker.")]
        [DefaultValue("")]
        [FilePickerParams(title: "Choose a File to load from")]
        public string File { get; set; } = "";

        [DisplayName("Folder Picker")]
        [Description("Opens a file picker but locked to only allow folder selections.")]
        [DefaultValue("")]
        [FolderPickerParams(
            initialFolderPath: Environment.SpecialFolder.Desktop,
            userCanEditPathText: false,
            title: "Custom Folder Select",
            okButtonLabel: "Choose Folder",
            fileNameLabel: "ModFolder",
            multiSelect: true,
            forceFileSystem: true)]
        public string Folder { get; set; } = "";*/
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
