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
    class EmptyProperty : WObject
    {
        private const int HUNGER = 0;
        private const int ENERGY = 2;
        private const int FOODSTORES = 0;

        private int hungerRate = 0; //Rate of consumption for food


        public EmptyProperty(Texture2D spriteSheet, Vector2 startPos, int ownID)
            : base(spriteSheet, startPos, ownID)
        {
            setInteract(true);
            util = new Utility(HUNGER, ENERGY, FOODSTORES);
            setCollide(false);
            setStatic(true);
        }
        public EmptyProperty(Texture2D spriteSheet, Vector2 startPos)
            : base(spriteSheet, startPos)
        {
            setInteract(true);
            util = new Utility(HUNGER, ENERGY, FOODSTORES);
            setCollide(false);
            setStatic(true);
        }

        public override Utility Eat()
        {
           return new Utility(0, 0, 0);
        }

        public override Utility Sleep() { return new Utility(0, ENERGY, 0); }
        public override Utility Work() { return new Utility(0, 0, 0); }
    }
}