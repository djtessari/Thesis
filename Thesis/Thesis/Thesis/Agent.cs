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
        public List<WObject> knowledge;
        public float speed = 5.0f;
        public Vector2 destination;
        public Vector2 waypoint;
        private Vector2 D1 = new Vector2(200, 0);
        private Vector2 D2 = new Vector2(400, 550);
        private bool stopNow = false;
        private bool WPSet = false;
        private bool CDresolved = true;
        private Stack<Vector2> waypoints;
        private List<int> plan;
        private Utility goal;
        private bool hold = false;

        public Utility util;
        #endregion


        public Agent(Texture2D spriteSheet, Vector2 startPos, int logicNum): base(spriteSheet, startPos)
        {
            setLogicType = logicNum;
            energy = 100;
            setDest(D1);
            waypoints = new Stack<Vector2>();
            util = new Utility(1000,1000);
            plan = new List<int>();
            knowledge = new List<WObject>();
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
                    Console.WriteLine("Out of bounds!");
                    Console.WriteLine("X position = " + position.X);
                    Console.WriteLine("Y Position = " + position.Y);
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
            if (WPSet)
            {
                moveTo(waypoint);
                if (atWP())
                {
                    WPSet = false;
                }
            }
            else
            {
                /*System.Drawing.Point p = System.Windows.Forms.Control.MousePosition;
                Vector2 cursor = new Vector2(p.X, p.Y);
                setDest(cursor);*/

                moveTo(destination);
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
                Console.WriteLine("Destination reached");
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
                Console.WriteLine("Waypoint reached");
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
            //Level 1
            if (util.hunger < util.concern)
            {
                goal = new Utility(util.stable, util.stable);
                Console.WriteLine("Food Concern");
                if (util.hunger < util.critical)
                {
                    Console.WriteLine("Food Critical");
                    /*goal hunger = concern*/
                }
            }
            
            /*
            if (util.energy < util.concern)
            {   //Goal energy = stable
                if (util.energy < util.critical)
                { 
                    //goal energy = concern
              * }
            }/**/

            /*if (level2) //If both hunger and energy are not critical
            {
                //level 2 evaluation
            }*/

            //find level 1
            if (goal != null)
            {
                if (!util.Met(goal))
                {
                    WObject choice = null;
                    foreach (WObject o in knowledge)
                    {
                        choice = o;
                    }
                    if (choice != null)
                        setDest(choice.getPos());
                }
                else
                {
                    goal = null;
                    setDest(D2);
                }
            }

            if (atDest())
            {
                if (destination.Equals(D1)) destination = D2;
                else if (destination.Equals(D2)) destination = D1;
            }
            
        }
        private void basicLogic()
        {
            
        }

        public void Eval(WObject o)
        {
            if (o.getPos() == destination || o.getPos() == waypoint)
            {
                Use(o.getUtil());
            }
        }
        private void Use(Utility u)
        {
            util.Add(u);
        }
        #endregion
    }

}
