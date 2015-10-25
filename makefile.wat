
# TIC.EXE and HERETIC.EXE makefile

# --------------------------------------------------------------------------
#
#      4r  use 80486 timings and register argument passing
#       c  compile only
#      d1  include line number debugging information
#      d2  include full sybolic debugging information
#      ei  force enums to be of type int
#       j  change char default from unsigned to signed
#      oa  relax aliasing checking
#      od  do not optimize
#  oe[=#]  expand functions inline, # = quads (default 20)
#      oi  use the inline library functions
#      om  generate inline 80x87 code for math functions
#      ot  optimize for time
#      ox  maximum optimization
#       s  remove stack overflow checks
#     zp1  align structures on bytes
#      zq  use quiet mode
#  /i=dir  add include directories
#
# --------------------------------------------------------------------------

CCOPTS = $(EXTERNOPT) /omaxet /zp1 /4r /ei /j /zq /i=3rdparty\include
#CCOPTS = /d2 /odam /zp1 /4r /ei /j /zq /i=3rdparty\include

LOCOBJS = &
 i_cyber.obj &
 i_ibm_a.obj &
 i_sound.obj &
 linear.obj

GLOBOBJS = &
 am_map.obj &
 ct_chat.obj &
 d_main.obj &
 d_net.obj &
 deh_ammo.obj		 &
 deh_cht.obj		 &
 deh_io.obj		 &
 deh_frme.obj		 &
 deh_map.obj		 &
 deh_main.obj		 &
 deh_misc.obj		 &
 deh_ptr.obj		 &
 deh_snd.obj		 &
 deh_text.obj		 &
 deh_thng.obj		 &
 deh_wpn.obj		 &
 g_game.obj &
 f_finale.obj &
 info.obj &
 in_lude.obj &
 mn_menu.obj &
 m_misc.obj &
 md5.obj &
 p_ceilng.obj &
 p_doors.obj &
 p_enemy.obj &
 p_floor.obj &
 p_inter.obj &
 p_lights.obj &
 p_map.obj &
 p_maputl.obj &
 p_mobj.obj &
 p_plats.obj &
 p_pspr.obj &
 p_setup.obj &
 p_sight.obj &
 p_spec.obj &
 p_switch.obj &
 p_telept.obj &
 p_tick.obj &
 p_user.obj &
 r_bsp.obj &
 r_data.obj &
 r_draw.obj &
 r_main.obj &
 r_plane.obj &
 r_segs.obj &
 r_things.obj &
 sb_bar.obj &
 sounds.obj &
 tables.obj &
 v_video.obj &
 w_wad.obj &
 w_merge.obj &
 z_zone.obj

tic.exe : $(LOCOBJS) $(GLOBOBJS) i_ibm.obj
 wlink @tic.wlk
 copy tic.exe striptic.exe
 wstrip -n striptic.exe
 4gwbind 4gwpro.exe striptic.exe heretic.exe -V 
# sb /R /O heretic.exe #Uncomment this to use DOS32/a

i_ibm.obj:
 wcc386 /zp1 /4r /zq /ei /i=3rdparty\include /j i_ibm.c

.c.obj :
 wcc386 $(CCOPTS) $[*

.asm.obj :
 tasm /mx $[*

clean : .SYMBOLIC
 del *.obj
 del *.dsg
 del *.cfg
 del *.wad
 del *.deh
 del *.dsg
 del *.sym
 del *.map
 del out.txt

final : .SYMBOLIC
 wlink @tic.wlk
 copy tic.exe striptic.exe
 wstrip -n striptic.exe
 4gwbind 4gwpro.exe striptic.exe heretic.exe -V 
# sb /R /O heretic.exe #Uncomment this to use DOS32/a
