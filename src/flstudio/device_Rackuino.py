# name=Rackuino
# url=https://github.com/bliepp/Rackuino

import transport
import device
import ui
import midi


BUTTONS = [102, 103, 104, 105, 106, 107]
CHANNEL = 11 # channel 12, since MIDI API is 0 based!


class Rackuino():
    def __init__(self):
        self.map = {
            # default values of first BUTTONS row
            BUTTONS[0]: lambda: transport.globalTransport(midi.FPT_Loop, 1),            # pattern/song mode
            BUTTONS[1]: lambda: transport.globalTransport(midi.FPT_Play, 1),            # play/pause
            BUTTONS[2]: lambda: transport.globalTransport(midi.FPT_Stop, 1),            # stop
            BUTTONS[3]: lambda: transport.globalTransport(midi.FPT_Record, 1),          # recording
            BUTTONS[4]: lambda: transport.globalTransport(midi.FPT_Metronome, 1),       # metronome
            BUTTONS[5]: lambda: transport.globalTransport(midi.FPT_LoopRecord, 1),      # loop recording
        }
        self.lights_off()
        self.set_lights()

    def lights_off(self):
        if device.isAssigned():
            for i in range(len(BUTTONS)):
                device.midiOutMsg(176, CHANNEL, BUTTONS[i], 0) # TODO: set correct midi msg status byte

    def set_lights(self):
        if device.isAssigned():
            switch = lambda cond: (176, 127*cond)

            status, value = switch(transport.getLoopMode())
            device.midiOutMsg(status, CHANNEL, BUTTONS[0], value)

            status, value = switch(transport.isPlaying())
            device.midiOutMsg(status, CHANNEL, BUTTONS[1], value)

            status, value = switch(transport.isRecording())
            device.midiOutMsg(status, CHANNEL, BUTTONS[3], value)

            status, value = switch(ui.isMetronomeEnabled())
            device.midiOutMsg(status, CHANNEL, BUTTONS[4], value)

            status, value = switch(ui.isLoopRecEnabled())
            device.midiOutMsg(status, CHANNEL, BUTTONS[5], value)

    def OnControlChange(self, event):
        if event.midiChan == CHANNEL:
            trigger = self.map.get(event.data1, lambda: None)
            if event.data2 > 0: # all switches in momentary mode
                trigger()
            event.handled = True



rackuino = Rackuino()


def OnRefresh(flags):
    rackuino.lights_off()
    rackuino.set_lights()

def OnControlChange(event):
    rackuino.OnControlChange(event)
