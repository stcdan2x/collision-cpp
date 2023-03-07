// Called when a key is pressed
void handleKeypress(unsigned char key, int x, int y)
{ // The current mouse coordinates
   switch (key)
   {
   case (27): // ESC
      exit(0);
      break;
   case (13): // Enter
      exit(0);
      break;
   case (32): // SpaceBar
      cbForPP(0);
      break;
   }
}

void handleSpecialKeypress(int key, int x, int y)
{ // The current mouse coordinates
   switch (key)
   {
   case (GLUT_KEY_UP): // Up Arrow
      obj_pos[1] += 0.05;
      break;
   case (GLUT_KEY_DOWN): // Down Arrow
      obj_pos[1] -= 0.05;
      break;
   case (GLUT_KEY_LEFT): // Down Arrow
      obj_pos[0] -= 0.05;
      break;
   case (GLUT_KEY_RIGHT): // Down Arrow
      obj_pos[0] += 0.05;
      break;
   }
}

// call back function for increasing speed of all balls
void cbIncSpeed()
{
   for (int i = 0; i < num_balls; i++)
   {
      if (Balls[i].getVelocityX() < 0)
         Balls[i].setVelocityX(Balls[i].getVelocityX() - 0.01);
      else
         Balls[i].setVelocityX(Balls[i].getVelocityX() + 0.01);
      if (Balls[i].getVelocityY() < 0)
         Balls[i].setVelocityY(Balls[i].getVelocityY() - 0.01);
      else
         Balls[i].setVelocityY(Balls[i].getVelocityY() + 0.01);
      if (threeD)
      {
         if (Balls[i].getVelocityZ() < 0)
            Balls[i].setVelocityZ(Balls[i].getVelocityZ() - 0.01);
         else
            Balls[i].setVelocityZ(Balls[i].getVelocityZ() + 0.01);
      }
   }
}

// call back function for increasing speed of ball with id 'bid'
void cbIncBallSpeed(int bid)
{
   if (Balls[bid].getVelocityX() < 0)
      Balls[bid].setVelocityX(Balls[bid].getVelocityX() - 0.01);
   else
      Balls[bid].setVelocityX(Balls[bid].getVelocityX() + 0.01);
   if (Balls[bid].getVelocityY() < 0)
      Balls[bid].setVelocityY(Balls[bid].getVelocityY() - 0.01);
   else
      Balls[bid].setVelocityY(Balls[bid].getVelocityY() + 0.01);
   if (threeD)
   {
      if (Balls[bid].getVelocityZ() < 0)
         Balls[bid].setVelocityZ(Balls[bid].getVelocityZ() - 0.01);
      else
         Balls[bid].setVelocityZ(Balls[bid].getVelocityZ() + 0.01);
   }
}

// call back function for decreasing speed of all balls
void cbDecSpeed()
{
   for (int i = 0; i < num_balls; i++)
   {
      if (Balls[i].getVelocityX() < 0)
         Balls[i].setVelocityX(Balls[i].getVelocityX() + 0.01);
      else
         Balls[i].setVelocityX(Balls[i].getVelocityX() - 0.01);
      if (Balls[i].getVelocityY() < 0)
         Balls[i].setVelocityY(Balls[i].getVelocityY() + 0.01);
      else
         Balls[i].setVelocityY(Balls[i].getVelocityY() - 0.01);
      if (threeD)
      {
         if (Balls[i].getVelocityZ() < 0)
            Balls[i].setVelocityZ(Balls[i].getVelocityZ() + 0.01);
         else
            Balls[i].setVelocityZ(Balls[i].getVelocityZ() - 0.01);
      }
   }
}

// call back function for decreasing speed of ball with id 'bid'
void cbDecBallSpeed(int bid)
{
   if (Balls[bid].getVelocityX() < 0)
      Balls[bid].setVelocityX(Balls[bid].getVelocityX() + 0.01);
   else
      Balls[bid].setVelocityX(Balls[bid].getVelocityX() - 0.01);
   if (Balls[bid].getVelocityY() < 0)
      Balls[bid].setVelocityY(Balls[bid].getVelocityY() + 0.01);
   else
      Balls[bid].setVelocityY(Balls[bid].getVelocityY() - 0.01);
   if (threeD)
   {
      if (Balls[bid].getVelocityZ() < 0)
         Balls[bid].setVelocityZ(Balls[bid].getVelocityZ() + 0.01);
      else
         Balls[bid].setVelocityZ(Balls[bid].getVelocityZ() - 0.01);
   }
}

// call back function for setting Default Theme
void cbDefault()
{
   thm = Default;
}

// call back function for setting High Contrast Theme
void cbHighContrast()
{
   thm = HighContrast;
}

// call back function for setting Black Metallic Theme
void cbBlackMetallic()
{
   thm = BlackMetallic;
}

// call back function for setting Pool Theme
void cbPool()
{
   thm = Pool;
}

// call back function for play and pause
void cbForPP(int value)
{
   playing = !(playing);
}

void cbTheme(int value)
{
   if (threeD)
   {
      radio2D->disable();
      radio3D->enable();
   }
   else
   {
      radio2D->enable();
      radio3D->disable();
   }
   switch (thm_int)
   {
   case (0):
      cbDefault();
      break;
   case (1):
      cbBlackMetallic();
      break;
   case (2):
      cbHighContrast();
      break;
   case (3):
      cbPool();
      break;
   }
}

// call back function when size changes
void cbSameSize(int value)
{
   if (same_size)
   {
      for (int i = 0; i < max_balls; i++)
         Balls[i].setRadius(min_radius);
   }
   else
   {
      for (int i = 0; i < max_balls; i++)
         Balls[i].setRadius(max((double)(abs(ran()) / 4), min_radius));
   }
}
// call back function when color changes
void cbSameColor(int value)
{
   if (ball_selected == -1)
   {
      if (same_color)
      {
         sbRed->enable();
         sbGreen->enable();
         sbBlue->enable();
         gb->enable();

         color clr = {globalR / 256, globalG / 256, globalB / 256};
         for (int i = 0; i < num_balls; i++)
         {
            Balls[i].setColor(clr);
         }
      }
      else
      {
         sbRed->disable();
         sbGreen->disable();
         sbBlue->disable();
         gb->disable();

         for (int i = 0; i < num_balls; i++)
         {
            Balls[i].setColor();
         }
      }
   }
   else
   {
      if (same_color)
      {
         sbRed->enable();
         sbGreen->enable();
         sbBlue->enable();
         gb->enable();

         color clr = {(float)globalR / 256, (float)globalG / 256, (float)globalB / 256};
         Balls[ball_selected].setColor(clr);
      }
      else
      {
         sbRed->disable();
         sbGreen->disable();
         sbBlue->disable();
         gb->disable();

         Balls[ball_selected].setColor();
      }
   }
}

// call back function when mode (2D/3D) changes
void cbMode(int value)
{
   if (threeD)
   {
      gb_enable->enable();
      gb_disable->enable();
   }
   else
   {
      gb_enable->disable();
      gb_disable->disable();
   }
   makeBalls();
   cbSameSize(1);
   cbSameColor(1);
   cbTheme(1);
   glutPostRedisplay();
}

// call back function for chosing color
void cbColorChooser(int value)
{
   unsigned char ret[3] = {(unsigned char)globalR, (unsigned char)globalG, (unsigned char)globalB};
   tinyfd_colorChooser("Choose Color", NULL, ret, ret);
   globalR = ret[0];
   globalG = ret[1];
   globalB = ret[2];
   cbSameColor(1);
}

// call back function for changing speed
void cbSpeed(int value)
{
   if (ball_selected == -1)
   {
      if (speed > prev_speed)
      {
         int count = speed - prev_speed;
         while (count--)
            cbIncSpeed();
      }
      else if (speed < prev_speed)
      {
         int count = prev_speed - speed;
         while (count--)
            cbDecSpeed();
      }
      prev_speed = speed;
   }
   else
   {
      if (speed > prev_speed)
      {
         int count = speed - prev_speed;
         while (count--)
            cbIncBallSpeed(ball_selected);
      }
      else if (speed < prev_speed)
      {
         int count = prev_speed - speed;
         while (count--)
            cbDecBallSpeed(ball_selected);
      }
      prev_speed = speed;
   }
}

void control_cb(int control)
{
   if (control == ENABLE_ID)
   {
      glui2->enable();
   }
   else if (control == DISABLE_ID)
   {
      glui2->disable();
   }
}
