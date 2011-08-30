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

        public WObject(Texture2D spriteSheet, Vector2 startPos): base(spriteSheet, startPos)
        {
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

        new public void Update(GameTime gameTime)
        {
        }
    }
}
