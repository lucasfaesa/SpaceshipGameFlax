using System;
using System.Collections.Generic;
using FlaxEngine;

namespace Game;

/// <summary>
/// ShipMovement Script.
/// </summary>
public partial class ShipMovement : Script
{
    public float ReturnShipSpeed
    {
        get { return GetShipSpeed(); }
    }
}
