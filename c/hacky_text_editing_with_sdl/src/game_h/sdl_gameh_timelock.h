#ifndef SDL_GAMEH_TIMELOCK
#define SDL_GAMEH_TIMELOCK

typedef struct Timelock {
  int lockAt;
  int startedAt;
  int unlockDelta;
  int unlockCount;
} Timelock;

void Timelock_Init(Timelock* tl, int lockAt)
{
  tl->lockAt = lockAt;
  tl->startedAt = SDL_GetTicks();
  tl->unlockCount = 0;
  tl->unlockDelta = 0;
}

void Timelock_Start(Timelock* tl)
{
  tl->startedAt = SDL_GetTicks();
}

int Timelock_Delta(Timelock* tl)
{
  return SDL_GetTicks() - tl->startedAt;
}

int Timelock_IsLocked(Timelock* tl)
{
  return tl->lockAt <= Timelock_Delta(tl);
}

void Timelock_Unlock(Timelock* tl)
{
  tl->unlockDelta = Timelock_Delta(tl);
  tl->unlockCount++;
  tl->startedAt = SDL_GetTicks();
}

void Timelock_Recount(Timelock* tl)
{
  tl->unlockCount = 0;
}

#endif