#ifndef EVENT_ACTION_HH
#define EVENT_ACTION_HH

#include "G4UserEventAction.hh"
#include "globals.hh"

class event_action : public G4UserEventAction {
public:
  event_action();
  ~event_action() override = default;

  void BeginOfEventAction(const G4Event*) override;
  void EndOfEventAction(const G4Event*) override;

  void add_edep(G4double e) { edep += e; }

private:
  G4double edep;
};

#endif
