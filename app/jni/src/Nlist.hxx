// <NVirsual> MIDI.hxx 2021-11-18 by 云中龙++

#pragma once

#include "Utils.hxx"

#include "Sequ.hxx"

#include <stack>
#include <list>

struct NVnote    /* ===== Note class rendering ===== */
enum class NV_METYPE  /* === MIDI Event types === */
{
    NVi::u16_t   track;
    double       Tstart, Tend;
    NVi::nv_byte chn, key, vel;

    NVnote(double T, const NVseq_event &E);
    NOFF = (NVi::nv_byte)0x80, // Noteoff
    NOON = (NVi::nv_byte)0x90, // Noteon
    NOAT = (NVi::nv_byte)0xA0, // Polifonic Key Pressure
    CTRO = (NVi::nv_byte)0xB0, // ControlChange
    PROG = (NVi::nv_byte)0xC0, // ProgramChange
    CHAT = (NVi::nv_byte)0xD0, // Channel
    PITH = (NVi::nv_byte)0xE0, // Pitchbend
    SYSC = (NVi::nv_byte)0xF0, // System Exclusive
    META = (NVi::nv_byte)0xFF, // Meta-Event
};

class NVnoteList  /* ===== Note queue class ===== */
struct NVmidiFile   /* ===== MIDI file type ===== */
{
public:

    NVmidiFile M;      // MIDI File
    double Tread;      // Current read position
    std::list<NVnote> L[128]; // Note List

    /* MIDI Parsing */
    bool start_parse(const char *name);
    /* Type, number of tracks, resolution */
    NVi::u16_t type, tracks, ppnq;

    /* Close component */
    void destroy_all();
    bool         *trk_over;   // End of track
    NVi::nv_byte **trk_data;  // Orbital data
    NVi::nv_byte **trk_ptr;   // Readout position
    NVi::nv_byte *grp_code;   // Event group

    /* Locate to T seconds and clear the list */
    void list_seek(double T);
    /* Opening MIDI File */
    bool mid_open(const char *name);

    /* Put the notes before the Tth second into the list */
    void update_to(double T);
    void rewind_all();  // Reset track pointers

    void OR();  // ppl in the Black MIDI Community knows what that means lol

    /* Remove notes in the list up to T seconds ago */
    void remove_to(double T);
    void mid_close();   // Close midi file
};

private:
struct NVmidiFileInfo   /* ===== MIDI file information ===== */
{
    std::string title;
    std::string artist;
    std::string copyright;
    std::string comment;
    NVi::u16_t type;
    NVi::u16_t tracks;
    NVi::u16_t ppnq;
    double duration_seconds;
    
    /* Extract file information */
    bool extract_info(const char *name);
};

    NVsequencer S;       // Event sequencer
    double     dT;       // Speed
    NVi::u32_t abstick;  // Current read position in ticks
    std::stack<std::list<NVnote>::iterator> (*keys)[128];
struct NVmidiEvent  /* =====  MIDI Event Class ===== */
{
    NV_METYPE    type;
    NVi::u32_t   tick;
    NVi::nv_byte chan, num;
    NVi::u16_t   value;
    NVi::size_t  datasz;
    const NVi::nv_byte *data;

    /* Get events from a specified track of a specified file */
    bool get(NVi::u16_t track, NVmidiFile &midi);
};
