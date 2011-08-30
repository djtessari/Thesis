using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.GamerServices;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Media;

namespace Thesis
{
    class Farmland : WObject
    {
        public Farmland(Texture2D spriteSheet, Vector2 startPos)
            : base(spriteSheet, startPos)
        {
            setInteract(true);
            util = new Utility(5, 5);
            setCollide(false);
            setStatic(true);
        }
    }
}
