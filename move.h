int move_up(int ypos){
  ypos -= 32;
  if (ypos < 0) {
    ypos += 32;
  }
  return ypos;
}

int move_down(int ypos){
  ypos += 32;
  if (ypos > SCREEN_HEIGHT - 32) {
    ypos -= 32;
  }
  return ypos;
}

int move_right(int xpos) {
  xpos += 32;
  if (xpos > SCREEN_WIDTH - 32) {
    xpos -= 32;
  }
  return xpos;
}

int move_left(int xpos) {
  xpos -= 32;
  if (xpos < 0) {
    xpos -= 32;
  }
  return xpos;
}
