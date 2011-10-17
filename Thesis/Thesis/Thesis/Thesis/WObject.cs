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
    class WObject: Entity
    {
        private bool _canInteract;
        public Utility util;
        public int ownerID;

        public WObject(Texture2D spriteSheet, Vector2 startPos): base(spriteSheet, startPos)
        {
            ownerID = 0; //No owner
            util = new Utility(0, 0);
            _canInteract = false;
            setCollide(true);
            setStatic(true);
        }

        public WObject(Texture2D spriteSheet, Vector2 startPos, int ownID)
            : base(spriteSheet, startPos)
        {
            ownerID = ownID;
            util = new Utility(0, 0);
            _canInteract = false;
            setCollide(true);
            setStatic(true);
        }

        public void setInteract(bool b)
        {
            _canInteract = b;
        }
        public bool canInteract()
        {
            return _canInteract;
        }

        public Utility getUtil()
        {
            return util;
        }

        public virtual Utility Eat(){return null;}
        public virtual Utility Sleep(){return null;}
        public virtual Utility Work(){return null;}

        new public void Update(GameTime gameTime)
        {
            if (util != null)
                util.Decay();
        }
    }
}
