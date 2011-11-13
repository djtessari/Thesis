using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.GamerServices;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Media;

namespace Thesis
{
    class Agent: Entity
    {
        #region vars
        public int setLogicType; //0 = 'basic', 1 = 'maslow'
        public int energy;
        public int agentID;
        public int health = 100;

        public List<WObject> knowledge;
        public List<WObject> property;
        public List<Agent> people;
        public WObject home;
        public WObject goalObject;

        public float speed = 5.0f;
        public Vector2 destination;
        public Vector2 waypoint;
        private Boolean destSet = false;
        private Vector2 D1 = new Vector2(200, 0);
        private Vector2 D2 = new Vector2(400, 550);
        private bool stopNow = false;
        private bool WPSet = false;
        private bool CDresolved = true;
        private Stack<Vector2> waypoints;
        private List<int> plan;
        private Utility goal;
        private bool hold = false;
        private Boolean sleepHere = false;

        private const int BASE_SLEEP_ENERGY = 3;

        private const int ENERGY_DECAY = 1;
        private const int HUNGER_DECAY = 1;
        private const int FOOD_DECAY = 0;

        private string action = "";
        private const string EAT = "EAT";
        private const string SLEEP = "SLEEP";
        private const string WORK = "WORK";

        public Utility util;
        #endregion


        public Agent(Texture2D spriteSheet, Vector2 startPos, int logicNum, int id): base(spriteSheet, startPos)
        {            
            agentID = id;
            setLogicType = logicNum;
            energy = 100;
            setDest(D1);
            waypoints = new Stack<Vector2>();
            util = new Utility(1000,1000,0);            
            util.setDecay(HUNGER_DECAY, ENERGY_DECAY, FOOD_DECAY);
            util.setRecover(0,0,0);
            plan = new List<int>();
            knowledge = new List<WObject>();
            property = new List<WObject>();
            people = new List<Agent>();
            goal = new Utility(0,0,0);
            goalObject = null;
            home = null;

        }

        #region Inherited
        new public void Update(GameTime gameTime)
        {

            if (!stopNow)
            {
                runLogic();
                move();
                if (position.Y < 0 || position.X < 0)
                {
                    //Console.WriteLine("Out of bounds!");
                    //Console.WriteLine("X position = " + position.X);
                    //Console.WriteLine("Y Position = " + position.Y);
                    stopNow = true;
                }
                //util.Decay();
            }
        }
        new public void Draw(SpriteBatch spriteBatch)
        {
            base.Draw(spriteBatch);
        }
        #endregion

        #region MoveLogic
        private void move()
        {
            if (sleepHere)
            {
                util.energy = util.energy + BASE_SLEEP_ENERGY;
            }
            else if (WPSet)
            {
                moveTo(waypoint);
                if (atWP())
                {
                    WPSet = false;
                }
            }
            else
            {
                if (hasDest() && !atDest()) moveTo(destination);
            }
        }
        private void moveTo(Vector2 loc)
        {
            if (position != destination)
            {
                float yLength = position.Y - loc.Y;
                float xLength = position.X - loc.X;
                double dist = Math.Sqrt((yLength * yLength) + (xLength * xLength));

                double theta = Math.Asin(Math.Abs(yLength) / dist);

                double xSpeed = Math.Cos(theta) * speed;
                double ySpeed = Math.Sin(theta) * speed;

                if (position.X > loc.X)
                {
                    xSpeed *= -1;
                }
                if (position.Y > loc.Y)
                {
                    ySpeed *= -1;
                }

                newPos(position.X + (float)xSpeed, position.Y + (float)ySpeed);
            }

        }
        public void resolveLR(WObject wobject)
        {
            CDresolved = false;
            if (position.Y > wobject.getPos().Y)  //vertical position reset to under object
            {
                newPos(position.X, wobject.getPos().Y + wobject.sprite.Height);
            }
            else  //vertical position reset to above object
            {
                newPos(position.X, wobject.getPos().Y - sprite.Height);
            }

            if (destination.X < wobject.getPos().X) //waypoint set to the left
            {
                waypoint = new Vector2(wobject.getPos().X - sprite.Width, position.Y);
            }
            else
            {
                waypoint = new Vector2(wobject.getPos().X + wobject.sprite.Width, position.Y);
            }
            _addWP(waypoint);
            WPSet = true;

        }
        public void resolveUD(WObject wobject)
        {
            if (position.X > wobject.getPos().X)  //horizontal position reset to right of object
            {
                newPos(wobject.getPos().X + wobject.sprite.Width, position.Y);
            }
            else  //horizontal position reset to left of object
            {
                newPos(wobject.getPos().X - sprite.Width, position.Y);
            }

            if (destination.Y < wobject.getPos().Y) //waypoint set to above object
            {
                waypoint = new Vector2(position.X, wobject.getPos().Y - sprite.Height);
            }
            else  //waypoint set below object
            {
                waypoint = new Vector2(position.X, wobject.getPos().Y + wobject.sprite.Height);
            }
            _addWP(waypoint);
            WPSet = true;
        }
        private bool atDest()
        {

            int xCheck = (int)(position.X - destination.X);
            int yCheck = (int)(position.Y - destination.Y);

            if (Math.Abs(xCheck) < 5 && Math.Abs(yCheck) < 5)
            {
                position = destination;
                //Console.WriteLine("Destination reached");
                return true;
            }
            return false;
        }
        private bool atWP()
        {
            int xCheck = (int)(position.X - waypoint.X);
            int yCheck = (int)(position.Y - waypoint.Y);

            if (Math.Abs(xCheck) < 5 && Math.Abs(yCheck) < 5)
            {
                position = waypoints.Pop();
                CDresolved = true;
                //Console.WriteLine("Waypoint reached");
                return true;
            }
            return false;
        }
        #endregion

        #region Getter/Setters
        public void setDest(Vector2 dest)
        {
            destination = dest;
        }

        public void setWP(Vector2 wp)
        {
            waypoint = wp;
        }


        private void newPos(int x, int y)
        {
            position = new Vector2(x, y);
        }
        private void newPos(float x, float y)
        {
            position = new Vector2(x, y);
        }

        private void _addWP(Vector2 wp)
        {
            if (waypoints.Count != 0)
            {
                if (waypoints.Peek() != wp)
                {
                    waypoints.Push(wp);
                }
            }
            else waypoints.Push(wp);
        }
        public void addWP(Vector2 wp)
        {
            if (CDresolved)
            {
                _addWP(wp);
            }
        }
        public void AddKnowledge(WObject o)
        {
            if (knowledge.Contains(o))
            {
                knowledge.Remove(o);
            }
            knowledge.Add(o);
        }

        public void SetProperty(List<WObject> o)
        {
            property = o;
        }

        public void AddProperty(WObject o)
        {
            if (property.Contains(o))
            {
                property.Remove(o);
            }
            property.Add(o);
        }
        #endregion

        #region Logic
        public void runLogic()
        {
            switch (setLogicType)
            {
                case 0:
                    basicLogic();
                    break;
                case 1:
                    maslowLogic();
                    break;
                default:
                    stopNow = true;
                    break;
            }
        }


        /*
         * This logic code makes use of the utility metric to make its decisions in as close to an approximation to human behavior has possible,
         * basing its choices on Maslow's Heirarchy of Needs.  It is called on each update, and performs the following procedure:
         * 
         * 1. Calls the utility's Decay function, emulating regular use of resources such as food and energy.
         * 
         * 2. Examines remaining utility and determines what is the highest priority based on increasing preference to lower levels of the heirarchy.
         * For example, if the agent is low on hunger, they will attempt to find food.  If both hunger and energy (1st level) are satisfied
         * and there is no immediate danger(2nd level), the agent will reach out into social activities(3rd level)
         * 
         * 3. If there are no immedaite needs, the agent will attempt to predict a future possible need and if action is required, such as
         * working a farmland for food now so that there is food available later, even if the agent is not immedaitely hungry.
         * 
         * 4. Once the end result is determined, the agent will search through its knowledgebase for a world object that will satisfy its
         * decision.  World objects include houses, farmland, stores, and even people.  Agents have a limited 'vision', and must discover new
         * objects before they are added to its knowledgebase.  The choice of object to use will depend on its available and relevant utility, 
         * and its distance from the agent (particularly for time-critical utility like food).
         * 
         * 5. After an object to use is selected, the coordinates for that object are set as the new destination and the agent moves toward
         * their destination.          
         */
        private void maslowLogic()
        {
            //Note to self:  should the logic only be called at destinations/impulse events to cut down on aimless wandering/cycle use?

            //1. Calls the utility's Decay function, emulating regular use of resources such as food and energy.
            util.Decay();

            /*  
             * 2. Examines remaining utility and determines what is the highest priority based on increasing preference to lower levels of the heirarchy.               
             * For example, if the agent is low on hunger, they will attempt to find food.  If both hunger and energy (1st level) are satisfied               
             * and there is no immediate danger(2nd level), the agent will reach out into social activities(3rd level)
             */



            //Threat assessment
            //If attacked/threatened, threat assessment takes over until threat resolved
            
            //Determine threat level: "How likely am I to win in a fight?"
            //Direct Attack - Threat is fighting with agent
            /* 
             * Will attack enemy if past certain threat threshold, depending on health
             * If health < critical, use critical threat. (very likely to attack in all cases)
             * If health < concern, use concern threat.  (only fight if likely to win)
             * If health is stable, use stable threat.  (only fight if sure to win)
             */
            //Indirect attack - Threat is against property
            /*
             * Much more dependant on threat level and value of good.  
             * Determine some algorithm to attack only past a certain value based on these factors
             * 
             */

            //If the initiator stops attacking and tries to flee, 
            // let them escape unless meets an exception.

            //Level 1
            //If hunger < critical: Find a nearby food source, regardless of owner.
            //If Hunger < concern: Find best food source you own.
          
            //If Energy < critical: Find nearest place to lay down.
            //If Energy < concern: Make way to bed.

            //Level 2
            //If Food Store < critical: Work food sources
            //If Food Sources < critical: Find/create/claim sources
            //If Food Store < Concern: Work food sources
            //If Food Sources < Concern: Find/Create
            //Essentially, will work whatever sources are available, and if still has energy, create sources.
                        
            //Level 3
            //Unknown, maybe just have agents communicate on each other every once in a while.

            if (agentAttacked())
            {
                sleepHere = false;
                //Determine action
            }
            else if (propertyAttacked())
            {
                sleepHere = false;
                //Determine action
            }
            else
            {
                //Move on to other basic needs


                //Level 1
                //If hunger < critical: Find a nearby food source, regardless of owner.
                //If Hunger < concern: Find best food source you own.

                //If Energy < critical: Find nearest place to lay down.
                //If Energy < concern: Make way to bed.
                if (util.hunger < util.critical)
                {
                    //Console.WriteLine("Hunger Critical");
                    sleepHere = false;
                    goal.hunger = util.concern;
                    nearestFood();
                    
                }

                else if (util.energy < util.critical)
                {
                    //Console.WriteLine("Energy Critical");
                    goal.energy = util.concern;
                    nearestRest();
                }

                if (!hasDest())
                {
                    //No immediate hunger/sleep needs
                    if (util.hunger < util.concern)
                    {
                        goal.hunger = util.stable;
                        //Console.WriteLine("Hunger Concern");
                        sleepHere = false;
                        feedSelf();
                    }

                    else if (util.energy < util.concern)
                    {
                        goal.energy = util.stable;
                        //Console.WriteLine("Energy Concern");
                        goToBed();
                    }
                }

                if (!hasDest())
                {
                    //Is full and rested, can now work.

                    //Level 2

                    //If Food Store < Concern: Work food sources
                    //Else If Food Sources < Concern: Find/Create
                    //Essentially, will work whatever sources are available, and if still has energy, create sources.
                    if (util.foodStores < util.concern)
                    {
                        goal.foodStores = util.stable;
                        //Console.WriteLine("Food stores concern");
                        if(!getFoodSource()){

                            if (foodSourceConcern())
                            {
                                //Console.WriteLine("Food source concern");
                                createFoodSource();
                            }
                        }
                    }
                    else if (foodSourceConcern())
                    {
                        //Console.WriteLine("Food source concern");
                        createFoodSource();
                    }
                }

                if (!hasDest())
                {
                    
                    //Has enough food stability to socialize. For now, just stand still.                    
                }
            }

            if (atDest() && hasDest())
            {
                //Console.WriteLine(action);
                Boolean test = Use(goalObject);                
                if (util.Met(goal) || test)
                {
                    //Console.WriteLine("stores = " + util.foodStores);
                    //Console.WriteLine("hunger = " + util.hunger);
                    //Console.WriteLine("energy = " + util.energy);
                    destSet = false;                
                    
                }
                
            }
        }

        private double distanceTo(WObject o)
        {
            double f = Math.Sqrt(Math.Pow(o.getPos().X - getPos().X, 2) + Math.Pow(o.getPos().Y - getPos().Y, 2));
            return f;
        }

        private Boolean agentAttacked(){
            return false;
        }
        private Boolean propertyAttacked(){
            return false;
        }
        private Boolean hasFoodSources(){
            return false;
        }
        private Boolean foodSourceConcern()
        {
            return false;
        }
        private Boolean hasDest(){
            
            return destSet;
        }

        private void nearestFood()
        {
            WObject choice = null;

            //searches property first, since all options are safer.
            //Will only use unowned sources if no property in range.

            double range = (util.hunger * speed);
            foreach (WObject o in property)
            {
                if (distanceTo(o) < range && o.getUtil().foodStores > 0)
                {
                    if (choice == null) choice = o;
                    else
                    {
                        if (choice.getUtil().hunger < o.getUtil().hunger && o.getUtil().foodStores > 0)
                        {
                            if(distanceTo(o) < distanceTo(choice))
                                choice = o;                            
                        }
                    }
                }                
            }

            if (choice == null)  //No food owned, look for any food
            {
                foreach (WObject o in knowledge)
                {
                    if (distanceTo(o) < range && o.getUtil().foodStores > 0)
                    {
                        if (choice == null) choice = o;
                        else
                        {
                            if (choice.getUtil().hunger < o.getUtil().hunger && o.getUtil().foodStores > 0)
                            {
                                if (distanceTo(o) < distanceTo(choice))
                                choice = o;
                            }
                        }
                    }                
                }
            }
            if (choice == null)
            {
                //Wait to die.  So sad :(
                setDest(getPos());
            }
            else 
            {
                setDest(choice.getPos());
                goalObject = choice;
                destSet = true;
                action = EAT;                
            }
        }
      
        private void nearestRest()
        {
            WObject choice = null;

            //searches property first, since all options are safer.
            //Will only use unowned sources if no property in range.

            double range = (util.energy * speed);
            if (distanceTo(home) < range)
            {
                choice = home;
            }
            else
            {
                foreach (WObject o in property)
                {
                    if (distanceTo(o) < range)
                    {
                        if (choice == null) choice = o;
                        else
                        {
                            if (choice.getUtil().energy < o.getUtil().energy)
                            {
                                if (distanceTo(o) < distanceTo(choice))
                                choice = o;
                            }
                        }
                    }
                }

                if (choice == null)  //No food owned, look for any food
                {
                    foreach (WObject o in knowledge)
                    {
                        if (distanceTo(o) < range)
                        {
                            if (choice == null) choice = o;
                            else
                            {
                                if (choice.getUtil().energy < o.getUtil().energy)
                                {
                                    if (distanceTo(o) < distanceTo(choice))
                                    choice = o;
                                }
                            }
                        }
                    }
                }
            }
            if (choice == null)
            {
                //Rest where they lie
                setDest(getPos());
                sleepHere = true;
            }
            else
            {
                setDest(choice.getPos());
                goalObject = choice;
                destSet = true;
                action = SLEEP;
            }
        }
        
        private void feedSelf()
        {
            WObject choice = null;
            //Only searches property to find food.  Distance does not matter.            
            
            foreach (WObject o in property)
            {
                if (choice == null && o.getUtil().foodStores > 0) choice = o;
                else if (choice != null)
                {
                    if (choice.getUtil().hunger < o.getUtil().hunger && o.getUtil().foodStores > 0)
                    {
                        if (distanceTo(o) < distanceTo(choice))
                        choice = o;                        
                    }
                }                
            }
            if (choice != null)
            {
                setDest(choice.getPos());
                goalObject = choice;
                destSet = true;
                action = EAT;
            }
        }

        private void goToBed()
        {/*
            if (home != null)
            {
                setDest(home.getPos());
                action = SLEEP;
                destSet = true;
                goalObject = home;
            }     
          */
        }

        private Boolean getFoodSource()
        {
            //Console.WriteLine("getFoodSourceCalled");
            WObject choice = null;   
            int i = 1;
            
            foreach (WObject o in property)
            {
                //Console.WriteLine("Iteration " + i);
                i++;
                if (o.getUtil().foodStores > 0)
                {
                    if (choice == null) choice = o;
                    else
                    {
                        if (o.getUtil().foodStores > choice.getUtil().foodStores)
                        {                            
                            choice = o;                            
                        }
                    }
                }
            }   
            if (choice != null) 
            {
                
                setDest(choice.getPos());
                destSet = true;
                goalObject = choice;
                action = WORK;
                return true;                    
            }

            return false;
        }

        private void createFoodSource()
        {

        }

        /*    if (util.hunger < util.concern || util.energy < util.concern)
            {
                if (util.hunger < util.concern)
                {
                    //"I'm hungry, I should find food at low risk"
                    goal.hunger = util.stable;
                    Console.WriteLine("Hunger Concern");
                    if (util.hunger < util.critical)
                    {
                        //"I'm starving, if I don't take a risk I will die"
                        Console.WriteLine("Hunger Critical");
                        /*goal hunger = concern
                    }
                }

                if (util.energy < util.concern)
                {
                    //"I'm hurt/tired, I should go home"
                    goal.energy = util.stable;
                    Console.WriteLine("Energy Concern");
                    if (util.hunger < util.critical)
                    {
                        //"I'm about to die"
                        Console.WriteLine("Energy Critical");
                        /*goal hunger = concern
                    }
                }
            }
            //No level 1 Concerns, move on to level 2 + 3
            else
            {
                //If there exists an immediate threat to self or property, fight or flight.
                //
            }
            /*if (level2) //If both hunger and energy are not critical
            {
                //level 2 evaluation
            }

            //find level 1
            if (!goal.isEmpty())
            {
                if (!util.Met(goal))
                {
                    WObject choice = null;
                    foreach (WObject o in property)
                    {
                        choice = o;
                    }
                    if (choice != null)
                        setDest(choice.getPos());
                }
                else
                {
                    goal.Empty();
                    setDest(D2);
                }
            }

            if (atDest())
            {
                if (destination.Equals(D1)) destination = D2;
                else if (destination.Equals(D2)) destination = D1;
            }
         * 
            
        }*/
        private void basicLogic()
        {
            
        }

        public Boolean Use(WObject o)
        {
            //Console.WriteLine("Goal stores = " + goalObject.util.foodStores);
            //Console.WriteLine("Goal hunger = " + goalObject.util.hunger);
            //Console.WriteLine("Goal energy = " + goalObject.util.energy);

            
            if (action.CompareTo(EAT) == 0)
            {
                util.Add(o.Eat());
                util.foodStores = home.util.foodStores;                
            }
            else if (action.CompareTo(SLEEP) == 0) 
            {
                util.Add(o.Sleep());
                home.util.foodStores = util.foodStores;
            }
            else if (action.CompareTo(WORK) == 0)
            {              
                util.Add(o.Work());
                home.util.foodStores = util.foodStores;
            }
            if (o.util.foodStores <= 0) return true;
            return false;
            
        }
        
        #endregion
    }

}
