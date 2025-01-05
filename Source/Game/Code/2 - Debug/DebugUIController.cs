using System;
using System.Collections.Generic;
using System.Globalization;
using FlaxEngine;
using FlaxEngine.GUI;


namespace Game;


public class DebugUIController : Script
{
    
    [Header("Script References")] 
    [ShowInEditor] [Serialize] private ShipMovement shipMovement;
    
    [Header("UI References")]
    [ShowInEditor] [Serialize] private UIControl velocityVector;
    [ShowInEditor] [Serialize] private UIControl velocityMagnitude;
    
   private Label _velocityVectorLabel;
   private Label _velocityMagnitudeLabel;


   public override void OnStart()
   {
       _velocityVectorLabel = velocityVector.Get<Label>();
       _velocityMagnitudeLabel = velocityMagnitude.Get<Label>();
   }

   public override void OnUpdate()
   {
       _velocityVectorLabel.Text = $"Velocity: {shipMovement.ReturnShipVelocity.ToString(CultureInfo.InvariantCulture)}";
       _velocityMagnitudeLabel.Text = $"Velocity: {shipMovement.ReturnShipVelocity.Length}";
       // Here you can add code that needs to be called every frame
   }
}
