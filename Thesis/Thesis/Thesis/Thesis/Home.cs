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
    class Home : WObject
    {
        private const int HUNGER = 5;
        private const int ENERGY = 5;
        private const int FOODSTORES = 0;

        private int hungerRate = 5; //Rate of consumption for food


        public Home(Texture2D spriteSheet, Vector2 startPos, int ownID)
            : base(spriteSheet, startPos, ownID)
        {
            setInteract(true);
            util = new Utility(HUNGER, ENERGY, FOODSTORES);
            setCollide(false);
            setStatic(true);
        }
        public Home(Texture2D spriteSheet, Vector2 startPos)
            : base(spriteSheet, startPos)
        {
            setInteract(true);
            util = new Utility(HUNGER, ENERGY, FOODSTORES);
            setCollide(false);
            setStatic(true);
        }

        public override Utility Eat() 
        {
            //Console.WriteLine("Foodstores Home = " + util.foodStores);
            if (util.foodStores > hungerRate)
            {
                util.foodStores -= hungerRate;
                return new Utility(hungerRate, 0, 0);
            }

            int ret = util.foodStores;
            util.foodStores = 0;
            return new Utility(ret, 0, 0);
        }

        public override Utility Sleep() { return new Utility(0, ENERGY, 0); }
        public override Utility Work() { return new Utility(0, 0, FOODSTORES); }
    }
}