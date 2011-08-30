using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Thesis
{
    class Utility  //Provides the utility metrics to use for evaluating decisions
    {
        //Level 1 - Physiological. Food, Sleep
        public int hunger; //Increased with food.  Decreased with time.
        public int energy; //Increased with sleep + food.  Decreased with time/activity.

        public int stable = 1000; //Not used for comparison, but to keep agents from constantly going in and out of concern state
        public int concern = 500;
        public int critical = 150;

        //Decay Rates
        private int d_Hunger = 1;
        private int d_Energy = 1;

        //Level 2 - Safety. NYE

        public Utility()
        {
            hunger = 100;
            energy = 100;
        }

        public Utility(int h, int e)
        {
            hunger = h;
            energy = e;
        }

        public void Decay() //Called each update, subtracts decay from value
        {
            hunger -= d_Hunger;
            energy -= d_Energy;
        }

        public void Add(Utility u)
        {
            hunger += u.hunger;
            energy += u.energy;
        }


        public bool Met(Utility u)
        {
            if (u != null)
            {
                if (hunger < u.hunger)
                {
                    return false;
                }
                if (energy < u.energy)
                {
                    return false;
                }
            }
            return true;
        }
    }
}
