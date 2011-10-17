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
        private const int HUNGER = 2;
        private const int ENERGY = 2;
        private const int FOODSTORES = 1000;

        private const int FOOD_RECOVER = 1;

        private int hungerRate = 2;
        private int energyRate = 2;
        private int foodRate = 5;        

        public Farmland(Texture2D spriteSheet, Vector2 startPos, int ownID)
            : base(spriteSheet, startPos, ownID)
        {
            setInteract(true);
            util = new Utility(HUNGER, ENERGY, FOODSTORES);
            setCollide(false);
            setStatic(true);

            util.setRecover(0, 0, FOOD_RECOVER);
        }
        public Farmland(Texture2D spriteSheet, Vector2 startPos)
            : base(spriteSheet, startPos)
        {
            setInteract(true);
            util = new Utility(HUNGER, ENERGY, FOODSTORES);
            setCollide(false);
            setStatic(true);

            util.setDecay(0, 0, 0);
            util.setRecover(0, 0, FOOD_RECOVER);
        }
        
        public override Utility Eat() 
        {
            if (util.foodStores > hungerRate)
            {
                util.foodStores -= hungerRate;
                return new Utility(hungerRate, 0, 0);
            }

            int ret = util.foodStores;
            util.foodStores = 0;
            return new Utility(ret, 0, 0); 
        }

        public override Utility Sleep() { return new Utility(0, energyRate, 0); }

        public override Utility Work()
        {            
            if (util.foodStores > foodRate)
            {
                util.foodStores -= foodRate;
                return new Utility(0, -1, foodRate);
            }

            int ret = util.foodStores;
            util.foodStores = 0;
            return new Utility(0, -1, ret);
        }
    }
}
