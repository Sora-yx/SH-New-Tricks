using Heroes.Controller.Hook.Interfaces;
using Heroes.Controller.Hook.Interfaces.Definitions;
using Heroes.Controller.Hook.Interfaces.Structures.Interfaces;
using New_Tricks.Template;
using Reloaded.Hooks.ReloadedII.Interfaces;
using Reloaded.Mod.Interfaces;
using System.Runtime.InteropServices;

// this class is used to get input info from the mod dependency Controller.Hook
// this is needed because the original game does not provide d-pad or bumper information

namespace New_Tricks
{
    public class Controller
    {
        public WeakReference<IControllerHook> controllerHookReference {  get; set; }

        public Controller() { }

        const string modName = "New_TricksC.dll";

        [DllImport(modName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void UpdateInputState(uint buttonFlags, uint oneFramePressFlags, int port);



        private void OnInputReceived(IExtendedHeroesController inputs, int port)
        {
            UpdateInputState((uint)inputs.ButtonFlags, (uint)inputs.OneFramePressButtonFlag, port);
        }


        public void DependencyController_SetEvent()
        {
            if (controllerHookReference != null && controllerHookReference.TryGetTarget(out var controller))
            {
                controller.OnInput += OnInputReceived;
                Console.WriteLine("SH New Tricks Mod: successfully added OnInputReceived Event!");

            }
        }
    }
}
