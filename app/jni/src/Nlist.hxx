// <NVirsual> MIDI.hxx 2021-11-18 by 云中龙++

#pragma once

#include "Utils.hxx"

#include "MIDI.cxx"

struct NVmidiFile   /* ===== MIDI file type ===== */
{
    /* Type, number of tracks, resolution */
    NVi::u16_t type, tracks, ppnq;

    bool         *trk_over;   // End of track
    NVi::nv_byte **trk_data;  // Orbital data
    NVi::nv_byte **trk_ptr;   // Readout position
    NVi::nv_byte *grp_code;   // Event group

    /* Opening MIDI File */
    bool mid_open(const char *name);

    void rewind_all();  // Reset track pointers

    void mid_close();   // Close midi file
};

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
