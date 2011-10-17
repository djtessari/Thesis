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

namespace WindowsGame2
{
    class Agent: Entity
    {
        public int setLogicType;
        public int energy;
        public KeyValuePair <Entity, Vector2> knowledge;

        public Agent(int logicNum)
        {
            setLogicType = logicNum;
        }



        private void maslowLogic(){}
        private void basicLogic(){}
    }
}
