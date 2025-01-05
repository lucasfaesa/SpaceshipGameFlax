using System;
using System.Collections.Generic;
using System.Globalization;
using FlaxEngine;
using FlaxEngine.GUI;


namespace Game;


public class DebugUIController : Script
{

   [ShowInEditor] [Serialize] private UIControl speedLabel;
   [ShowInEditor] [Serialize] private ShipMovement shipMovement;
   
   private Label speedLabelLabel;


   public override void OnStart()
   {
       speedLabelLabel = speedLabel.Get<Label>();
   }

   public override void OnUpdate()
   {
       speedLabelLabel.Text = shipMovement.ReturnShipSpeed.ToString(CultureInfo.InvariantCulture);
       // Here you can add code that needs to be called every frame
   }
}
