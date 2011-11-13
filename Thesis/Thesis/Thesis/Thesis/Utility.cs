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

        //Level 2 - Safety.  Assess threats to Food and Health
        public int foodStores; //Stored food at home.  
        public int threat;  //Positive - Dangerous, Negative - Safe

        //Level 3 - Social.  Interacting with people

        public int stable = 1500; //Not used for comparison, but to keep agents from constantly going in and out of concern state
        public int concern = 700;
        public int critical = 300;

        //Decay Rates
        private int d_Hunger = 0;
        private int d_Energy = 0;
        private int d_FoodStores = 0;

        //Recover rates
        private int r_Hunger = 0;
        private int r_Energy = 0;
        private int r_FoodStores = 0;

        //Level 2 - Safety. NYE

        public Utility()
        {
            hunger = 100;
            energy = 100;
            foodStores = 0;
        }

        public Utility(int h, int e)
        {
            hunger = h;
            energy = e;
            foodStores = 0;
        }

        public Utility(int h, int e, int f)
        {
            hunger = h;
            energy = e;
            foodStores = f;
        }


        public void Decay() //Called each update, subtracts decay from value
        {
            hunger -= d_Hunger;
            energy -= d_Energy;
            foodStores -= d_FoodStores;

            hunger += r_Hunger;
            energy += r_Energy;
            foodStores += r_FoodStores;
        }

        public void setDecay(int h, int e, int f)
        {
            d_Hunger = h;
            d_Energy = e;
            d_FoodStores = f;
        }

        public void setRecover(int h, int e, int f)
        {
            r_Hunger = h;
            r_Energy = e;
            r_FoodStores = f;
        }

        public void Add(Utility u)
        {
            hunger += u.hunger;
            energy += u.energy;
            foodStores += u.foodStores;
        }

        public virtual Utility Eat() { return this; }
        public virtual Utility Sleep() { return this; }
        public virtual Utility Work() {
            Console.WriteLine("Foodstores Blank = " + foodStores);
            return this; }


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
                if (foodStores < u.foodStores)
                {
                    return false;
                }
            }
            return true;
        }

        public void Empty()
        {
            hunger = 0;
            energy = 0;
            foodStores = 0;
            threat = 0;
        }
        public bool isEmpty()
        {
            if (hunger == 0 && energy == 0 && foodStores == 0)
            {
                return true;
            }
            return false;
        }
    }
}
