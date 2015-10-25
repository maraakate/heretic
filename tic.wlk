# TIC.EXE Linker directive file

#option quiet
option map
option stack=65536
option stub=wstub
debug all
libpath %WATCOM%\lib386
libpath %WATCOM%\lib386\dos
libpath 3rdparty\libs
lib noemu387.lib
lib dmx
format os2 le
name tic

file i_cyber.obj
file i_ibm.obj
file i_ibm_a.obj
file snd_dmx.obj
file linear.obj

file am_map.obj
file ct_chat.obj
file d_main.obj
file d_net.obj
file deh_ammo.obj
file deh_cht.obj
file deh_frme.obj
file deh_io.obj
file deh_main.obj
file deh_map.obj
file deh_misc.obj
file deh_ptr.obj
file deh_snd.obj
file deh_text.obj
file deh_thng.obj
file deh_wpn.obj
file g_game.obj
file f_finale.obj
file info.obj
file in_lude.obj
file mn_menu.obj
file m_misc.obj
file md5.obj
file p_ceilng.obj
file p_doors.obj
file p_enemy.obj
file p_floor.obj
file p_inter.obj
file p_lights.obj
file p_map.obj
file p_maputl.obj
file p_mobj.obj
file p_plats.obj
file p_pspr.obj
file p_setup.obj
file p_sight.obj
file p_spec.obj
file p_switch.obj
file p_telept.obj
file p_tick.obj
file p_user.obj
file r_bsp.obj
file r_data.obj
file r_draw.obj
file r_main.obj
file r_plane.obj
file r_segs.obj
file r_things.obj
file s_sounds.obj
file sb_bar.obj
file sounds.obj
file tables.obj
file v_video.obj
file w_wad.obj
file z_zone.obj
