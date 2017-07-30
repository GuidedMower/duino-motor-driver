

void toggleEnable() {
  ENABLE_STATE = !ENABLE_STATE;
  dm.setEnable(ENABLE_STATE);
}
