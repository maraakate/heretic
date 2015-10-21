/*===========================================================================
* FMFREQ.H - Frequencey & Volume Tables for OPL-2 & OPL-3 Cards
*----------------------------------------------------------------------------
*                CONFIDENTIAL & PROPRIETARY INFORMATION 			     
*----------------------------------------------------------------------------
*             Copyright (C) 1993 Digital Expressions, Inc. 		     
*                        All Rights Reserved.		   		     
*----------------------------------------------------------------------------
* "This software is furnished under a license and may be used only 	     
* in accordance with the terms of such license and with the inclusion 	     
* of the above copyright notice. This software or any other copies 	     
* thereof may not be provided or otherwise made available to any other 	     
* person. No title to and ownership of the software is hereby transfered."   
*----------------------------------------------------------------------------
*                     Written by Paul J. Radek
*----------------------------------------------------------------------------
* $Log:   F:/DMX/INC/VCS/FMFREQ.H_V  $
*  
*     Rev 1.0   02 Oct 1993 15:18:38   pjr
*  Initial revision.
*---------------------------------------------------------------------------*/
#ifndef _FMFREQ_H
#define _FMFREQ_H

LOCAL BYTE VolTable[ 128 ] = 
{
	0,1,3,5,6,8,10,11,13,14,16,17,19,20,22,23,
	25,26,27,29,30,32,33,34,36,37,39,41,43,45,47,49,
	50,52,54,55,57,59,60,61,63,64,66,67,68,69,71,72,
	73,74,75,76,77,79,80,81,82,83,84,84,85,86,87,88,
	89,90,91,92,92,93,94,95,96,96,97,98,99,99,100,101,
	101,102,103,103,104,105,105,106,107,107,108,109,109,110,110,111,112,
	112,113,113,114,114,115,115,116,117,117,118,118,119,119,120,120,121,
	121,122,122,123,123,123,124,124,125,125,126,126,127,127
};


LOCAL WORD    fm_freq[] =
{
    0x0159, 0x0159, 0x0159, 0x0159, 0x0159, 0x0159, 0x0159, 0x0159, 
    0x0159, 0x0159, 0x0159, 0x0159, 0x0159, 0x0159, 0x0159, 0x0159, // Note:  0
    0x015A, 0x015B, 0x015C, 0x015E, 0x015F, 0x0160, 0x0161, 0x0163, 
    0x0164, 0x0165, 0x0167, 0x0168, 0x0169, 0x016B, 0x016C, 0x016D, // Note:  1
    0x016E, 0x0170, 0x0171, 0x0172, 0x0174, 0x0175, 0x0176, 0x0178, 
    0x0179, 0x017B, 0x017C, 0x017D, 0x017F, 0x0180, 0x0181, 0x0183, // Note:  2
    0x0184, 0x0186, 0x0187, 0x0188, 0x018A, 0x018B, 0x018D, 0x018E, 
    0x0190, 0x0191, 0x0193, 0x0194, 0x0195, 0x0197, 0x0198, 0x019A, // Note:  3
    0x019B, 0x019D, 0x019E, 0x01A0, 0x01A1, 0x01A3, 0x01A4, 0x01A6, 
    0x01A7, 0x01A9, 0x01AB, 0x01AC, 0x01AE, 0x01AF, 0x01B1, 0x01B2, // Note:  4
    0x01B4, 0x01B5, 0x01B7, 0x01B9, 0x01BA, 0x01BC, 0x01BD, 0x01BF, 
    0x01C1, 0x01C2, 0x01C4, 0x01C6, 0x01C7, 0x01C9, 0x01CA, 0x01CC, // Note:  5
    0x01CE, 0x01CF, 0x01D1, 0x01D3, 0x01D4, 0x01D6, 0x01D8, 0x01DA, 
    0x01DB, 0x01DD, 0x01DF, 0x01E0, 0x01E2, 0x01E4, 0x01E6, 0x01E7, // Note:  6
    0x01E9, 0x01EB, 0x01ED, 0x01EF, 0x01F0, 0x01F2, 0x01F4, 0x01F6, 
    0x01F8, 0x01F9, 0x01FB, 0x01FD, 0x01FF, 0x0201, 0x0203, 0x0205, // Note:  7
    0x0207, 0x0208, 0x020A, 0x020C, 0x020E, 0x0210, 0x0212, 0x0214, 
    0x0216, 0x0218, 0x021A, 0x021C, 0x021E, 0x0220, 0x0221, 0x0223, // Note:  8
    0x0225, 0x0227, 0x0229, 0x022B, 0x022D, 0x022F, 0x0231, 0x0234, 
    0x0236, 0x0238, 0x023A, 0x023C, 0x023E, 0x0240, 0x0242, 0x0244, // Note:  9
    0x0246, 0x0248, 0x024A, 0x024C, 0x024F, 0x0251, 0x0253, 0x0255, 
    0x0257, 0x0259, 0x025C, 0x025E, 0x0260, 0x0262, 0x0264, 0x0267, // Note: 10
    0x0269, 0x026B, 0x026D, 0x026F, 0x0272, 0x0274, 0x0276, 0x0279, 
    0x027B, 0x027D, 0x027F, 0x0282, 0x0284, 0x0286, 0x0289, 0x028B, // Note: 11
    0x028D, 0x0290, 0x0292, 0x0295, 0x0297, 0x0299, 0x029C, 0x029E, 
    0x02A1, 0x02A3, 0x02A5, 0x02A8, 0x02AA, 0x02AD, 0x02AF, 0x02B2, // Note: 12
    0x02B4, 0x02B7, 0x02B9, 0x02BC, 0x02BE, 0x02C1, 0x02C3, 0x02C6, 
    0x02C9, 0x02CB, 0x02CE, 0x02D0, 0x02D3, 0x02D6, 0x02D8, 0x02DB, // Note: 13
    0x02DD, 0x02E0, 0x02E3, 0x02E5, 0x02E8, 0x02EB, 0x02ED, 0x02F0, 
    0x02F3, 0x02F6, 0x02F8, 0x02FB, 0x02FE, 0x0301, 0x0303, 0x0306, // Note: 14
    0x0309, 0x030C, 0x030F, 0x0311, 0x0314, 0x0317, 0x031A, 0x031D, 
    0x0320, 0x0323, 0x0326, 0x0329, 0x032B, 0x032E, 0x0331, 0x0334, // Note: 15
    0x0337, 0x033A, 0x033D, 0x0340, 0x0343, 0x0346, 0x0349, 0x034C, 
    0x034F, 0x0352, 0x0356, 0x0359, 0x035C, 0x035F, 0x0362, 0x0365, // Note: 16
    0x0368, 0x036B, 0x036F, 0x0372, 0x0375, 0x0378, 0x037B, 0x037F, 
    0x0382, 0x0385, 0x0388, 0x038C, 0x038F, 0x0392, 0x0395, 0x0399, // Note: 17
    0x039C, 0x039F, 0x03A3, 0x03A6, 0x03A9, 0x03AD, 0x03B0, 0x03B4, 
    0x03B7, 0x03BB, 0x03BE, 0x03C1, 0x03C5, 0x03C8, 0x03CC, 0x03CF, // Note: 18
    0x03D3, 0x03D7, 0x03DA, 0x03DE, 0x03E1, 0x03E5, 0x03E8, 0x03EC, 
    0x03F0, 0x03F3, 0x03F7, 0x03FB, 0x03FE, 0x0601, 0x0603, 0x0605, // Note: 19
    0x0607, 0x0608, 0x060A, 0x060C, 0x060E, 0x0610, 0x0612, 0x0614, 
    0x0616, 0x0618, 0x061A, 0x061C, 0x061E, 0x0620, 0x0621, 0x0623, // Note: 20
    0x0625, 0x0627, 0x0629, 0x062B, 0x062D, 0x062F, 0x0631, 0x0634, 
    0x0636, 0x0638, 0x063A, 0x063C, 0x063E, 0x0640, 0x0642, 0x0644, // Note: 21
    0x0646, 0x0648, 0x064A, 0x064C, 0x064F, 0x0651, 0x0653, 0x0655, 
    0x0657, 0x0659, 0x065C, 0x065E, 0x0660, 0x0662, 0x0664, 0x0667, // Note: 22
    0x0669, 0x066B, 0x066D, 0x066F, 0x0672, 0x0674, 0x0676, 0x0679, 
    0x067B, 0x067D, 0x067F, 0x0682, 0x0684, 0x0686, 0x0689, 0x068B, // Note: 23
    0x068D, 0x0690, 0x0692, 0x0695, 0x0697, 0x0699, 0x069C, 0x069E, 
    0x06A1, 0x06A3, 0x06A5, 0x06A8, 0x06AA, 0x06AD, 0x06AF, 0x06B2, // Note: 24
    0x06B4, 0x06B7, 0x06B9, 0x06BC, 0x06BE, 0x06C1, 0x06C3, 0x06C6, 
    0x06C9, 0x06CB, 0x06CE, 0x06D0, 0x06D3, 0x06D6, 0x06D8, 0x06DB, // Note: 25
    0x06DD, 0x06E0, 0x06E3, 0x06E5, 0x06E8, 0x06EB, 0x06ED, 0x06F0, 
    0x06F3, 0x06F6, 0x06F8, 0x06FB, 0x06FE, 0x0701, 0x0703, 0x0706, // Note: 26
    0x0709, 0x070C, 0x070F, 0x0711, 0x0714, 0x0717, 0x071A, 0x071D, 
    0x0720, 0x0723, 0x0726, 0x0729, 0x072B, 0x072E, 0x0731, 0x0734, // Note: 27
    0x0737, 0x073A, 0x073D, 0x0740, 0x0743, 0x0746, 0x0749, 0x074C, 
    0x074F, 0x0752, 0x0756, 0x0759, 0x075C, 0x075F, 0x0762, 0x0765, // Note: 28
    0x0768, 0x076B, 0x076F, 0x0772, 0x0775, 0x0778, 0x077B, 0x077F, 
    0x0782, 0x0785, 0x0788, 0x078C, 0x078F, 0x0792, 0x0795, 0x0799, // Note: 29
    0x079C, 0x079F, 0x07A3, 0x07A6, 0x07A9, 0x07AD, 0x07B0, 0x07B4, 
    0x07B7, 0x07BB, 0x07BE, 0x07C1, 0x07C5, 0x07C8, 0x07CC, 0x07CF, // Note: 30
    0x07D3, 0x07D7, 0x07DA, 0x07DE, 0x07E1, 0x07E5, 0x07E8, 0x07EC, 
    0x07F0, 0x07F3, 0x07F7, 0x07FB, 0x07FE, 0x0A01, 0x0A03, 0x0A05, // Note: 31
    0x0A07, 0x0A08, 0x0A0A, 0x0A0C, 0x0A0E, 0x0A10, 0x0A12, 0x0A14, 
    0x0A16, 0x0A18, 0x0A1A, 0x0A1C, 0x0A1E, 0x0A20, 0x0A21, 0x0A23, // Note: 32
    0x0A25, 0x0A27, 0x0A29, 0x0A2B, 0x0A2D, 0x0A2F, 0x0A31, 0x0A34, 
    0x0A36, 0x0A38, 0x0A3A, 0x0A3C, 0x0A3E, 0x0A40, 0x0A42, 0x0A44, // Note: 33
    0x0A46, 0x0A48, 0x0A4A, 0x0A4C, 0x0A4F, 0x0A51, 0x0A53, 0x0A55, 
    0x0A57, 0x0A59, 0x0A5C, 0x0A5E, 0x0A60, 0x0A62, 0x0A64, 0x0A67, // Note: 34
    0x0A69, 0x0A6B, 0x0A6D, 0x0A6F, 0x0A72, 0x0A74, 0x0A76, 0x0A79, 
    0x0A7B, 0x0A7D, 0x0A7F, 0x0A82, 0x0A84, 0x0A86, 0x0A89, 0x0A8B, // Note: 35
    0x0A8D, 0x0A90, 0x0A92, 0x0A95, 0x0A97, 0x0A99, 0x0A9C, 0x0A9E, 
    0x0AA1, 0x0AA3, 0x0AA5, 0x0AA8, 0x0AAA, 0x0AAD, 0x0AAF, 0x0AB2, // Note: 36
    0x0AB4, 0x0AB7, 0x0AB9, 0x0ABC, 0x0ABE, 0x0AC1, 0x0AC3, 0x0AC6, 
    0x0AC9, 0x0ACB, 0x0ACE, 0x0AD0, 0x0AD3, 0x0AD6, 0x0AD8, 0x0ADB, // Note: 37
    0x0ADD, 0x0AE0, 0x0AE3, 0x0AE5, 0x0AE8, 0x0AEB, 0x0AED, 0x0AF0, 
    0x0AF3, 0x0AF6, 0x0AF8, 0x0AFB, 0x0AFE, 0x0B01, 0x0B03, 0x0B06, // Note: 38
    0x0B09, 0x0B0C, 0x0B0F, 0x0B11, 0x0B14, 0x0B17, 0x0B1A, 0x0B1D, 
    0x0B20, 0x0B23, 0x0B26, 0x0B29, 0x0B2B, 0x0B2E, 0x0B31, 0x0B34, // Note: 39
    0x0B37, 0x0B3A, 0x0B3D, 0x0B40, 0x0B43, 0x0B46, 0x0B49, 0x0B4C, 
    0x0B4F, 0x0B52, 0x0B56, 0x0B59, 0x0B5C, 0x0B5F, 0x0B62, 0x0B65, // Note: 40
    0x0B68, 0x0B6B, 0x0B6F, 0x0B72, 0x0B75, 0x0B78, 0x0B7B, 0x0B7F, 
    0x0B82, 0x0B85, 0x0B88, 0x0B8C, 0x0B8F, 0x0B92, 0x0B95, 0x0B99, // Note: 41
    0x0B9C, 0x0B9F, 0x0BA3, 0x0BA6, 0x0BA9, 0x0BAD, 0x0BB0, 0x0BB4, 
    0x0BB7, 0x0BBB, 0x0BBE, 0x0BC1, 0x0BC5, 0x0BC8, 0x0BCC, 0x0BCF, // Note: 42
    0x0BD3, 0x0BD7, 0x0BDA, 0x0BDE, 0x0BE1, 0x0BE5, 0x0BE8, 0x0BEC, 
    0x0BF0, 0x0BF3, 0x0BF7, 0x0BFB, 0x0BFE, 0x0E01, 0x0E03, 0x0E05, // Note: 43
    0x0E07, 0x0E08, 0x0E0A, 0x0E0C, 0x0E0E, 0x0E10, 0x0E12, 0x0E14, 
    0x0E16, 0x0E18, 0x0E1A, 0x0E1C, 0x0E1E, 0x0E20, 0x0E21, 0x0E23, // Note: 44
    0x0E25, 0x0E27, 0x0E29, 0x0E2B, 0x0E2D, 0x0E2F, 0x0E31, 0x0E34, 
    0x0E36, 0x0E38, 0x0E3A, 0x0E3C, 0x0E3E, 0x0E40, 0x0E42, 0x0E44, // Note: 45
    0x0E46, 0x0E48, 0x0E4A, 0x0E4C, 0x0E4F, 0x0E51, 0x0E53, 0x0E55, 
    0x0E57, 0x0E59, 0x0E5C, 0x0E5E, 0x0E60, 0x0E62, 0x0E64, 0x0E67, // Note: 46
    0x0E69, 0x0E6B, 0x0E6D, 0x0E6F, 0x0E72, 0x0E74, 0x0E76, 0x0E79, 
    0x0E7B, 0x0E7D, 0x0E7F, 0x0E82, 0x0E84, 0x0E86, 0x0E89, 0x0E8B, // Note: 47
    0x0E8D, 0x0E90, 0x0E92, 0x0E95, 0x0E97, 0x0E99, 0x0E9C, 0x0E9E, 
    0x0EA1, 0x0EA3, 0x0EA5, 0x0EA8, 0x0EAA, 0x0EAD, 0x0EAF, 0x0EB2, // Note: 48
    0x0EB4, 0x0EB7, 0x0EB9, 0x0EBC, 0x0EBE, 0x0EC1, 0x0EC3, 0x0EC6, 
    0x0EC9, 0x0ECB, 0x0ECE, 0x0ED0, 0x0ED3, 0x0ED6, 0x0ED8, 0x0EDB, // Note: 49
    0x0EDD, 0x0EE0, 0x0EE3, 0x0EE5, 0x0EE8, 0x0EEB, 0x0EED, 0x0EF0, 
    0x0EF3, 0x0EF6, 0x0EF8, 0x0EFB, 0x0EFE, 0x0F01, 0x0F03, 0x0F06, // Note: 50
    0x0F09, 0x0F0C, 0x0F0F, 0x0F11, 0x0F14, 0x0F17, 0x0F1A, 0x0F1D, 
    0x0F20, 0x0F23, 0x0F26, 0x0F29, 0x0F2B, 0x0F2E, 0x0F31, 0x0F34, // Note: 51
    0x0F37, 0x0F3A, 0x0F3D, 0x0F40, 0x0F43, 0x0F46, 0x0F49, 0x0F4C, 
    0x0F4F, 0x0F52, 0x0F56, 0x0F59, 0x0F5C, 0x0F5F, 0x0F62, 0x0F65, // Note: 52
    0x0F68, 0x0F6B, 0x0F6F, 0x0F72, 0x0F75, 0x0F78, 0x0F7B, 0x0F7F, 
    0x0F82, 0x0F85, 0x0F88, 0x0F8C, 0x0F8F, 0x0F92, 0x0F95, 0x0F99, // Note: 53
    0x0F9C, 0x0F9F, 0x0FA3, 0x0FA6, 0x0FA9, 0x0FAD, 0x0FB0, 0x0FB4, 
    0x0FB7, 0x0FBB, 0x0FBE, 0x0FC1, 0x0FC5, 0x0FC8, 0x0FCC, 0x0FCF, // Note: 54
    0x0FD3, 0x0FD7, 0x0FDA, 0x0FDE, 0x0FE1, 0x0FE5, 0x0FE8, 0x0FEC, 
    0x0FF0, 0x0FF3, 0x0FF7, 0x0FFB, 0x0FFE, 0x1201, 0x1203, 0x1205, // Note: 55
    0x1207, 0x1208, 0x120A, 0x120C, 0x120E, 0x1210, 0x1212, 0x1214, 
    0x1216, 0x1218, 0x121A, 0x121C, 0x121E, 0x1220, 0x1221, 0x1223, // Note: 56
    0x1225, 0x1227, 0x1229, 0x122B, 0x122D, 0x122F, 0x1231, 0x1234, 
    0x1236, 0x1238, 0x123A, 0x123C, 0x123E, 0x1240, 0x1242, 0x1244, // Note: 57
    0x1246, 0x1248, 0x124A, 0x124C, 0x124F, 0x1251, 0x1253, 0x1255, 
    0x1257, 0x1259, 0x125C, 0x125E, 0x1260, 0x1262, 0x1264, 0x1267, // Note: 58
    0x1269, 0x126B, 0x126D, 0x126F, 0x1272, 0x1274, 0x1276, 0x1279, 
    0x127B, 0x127D, 0x127F, 0x1282, 0x1284, 0x1286, 0x1289, 0x128B, // Note: 59
    0x128D, 0x1290, 0x1292, 0x1295, 0x1297, 0x1299, 0x129C, 0x129E, 
    0x12A1, 0x12A3, 0x12A5, 0x12A8, 0x12AA, 0x12AD, 0x12AF, 0x12B2, // Note: 60
    0x12B4, 0x12B7, 0x12B9, 0x12BC, 0x12BE, 0x12C1, 0x12C3, 0x12C6, 
    0x12C9, 0x12CB, 0x12CE, 0x12D0, 0x12D3, 0x12D6, 0x12D8, 0x12DB, // Note: 61
    0x12DD, 0x12E0, 0x12E3, 0x12E5, 0x12E8, 0x12EB, 0x12ED, 0x12F0, 
    0x12F3, 0x12F6, 0x12F8, 0x12FB, 0x12FE, 0x1301, 0x1303, 0x1306, // Note: 62
    0x1309, 0x130C, 0x130F, 0x1311, 0x1314, 0x1317, 0x131A, 0x131D, 
    0x1320, 0x1323, 0x1326, 0x1329, 0x132B, 0x132E, 0x1331, 0x1334, // Note: 63
    0x1337, 0x133A, 0x133D, 0x1340, 0x1343, 0x1346, 0x1349, 0x134C, 
    0x134F, 0x1352, 0x1356, 0x1359, 0x135C, 0x135F, 0x1362, 0x1365, // Note: 64
    0x1368, 0x136B, 0x136F, 0x1372, 0x1375, 0x1378, 0x137B, 0x137F, 
    0x1382, 0x1385, 0x1388, 0x138C, 0x138F, 0x1392, 0x1395, 0x1399, // Note: 65
    0x139C, 0x139F, 0x13A3, 0x13A6, 0x13A9, 0x13AD, 0x13B0, 0x13B4, 
    0x13B7, 0x13BB, 0x13BE, 0x13C1, 0x13C5, 0x13C8, 0x13CC, 0x13CF, // Note: 66
    0x13D3, 0x13D7, 0x13DA, 0x13DE, 0x13E1, 0x13E5, 0x13E8, 0x13EC, 
    0x13F0, 0x13F3, 0x13F7, 0x13FB, 0x13FE, 0x1601, 0x1603, 0x1605, // Note: 67
    0x1607, 0x1608, 0x160A, 0x160C, 0x160E, 0x1610, 0x1612, 0x1614, 
    0x1616, 0x1618, 0x161A, 0x161C, 0x161E, 0x1620, 0x1621, 0x1623, // Note: 68
    0x1625, 0x1627, 0x1629, 0x162B, 0x162D, 0x162F, 0x1631, 0x1634, 
    0x1636, 0x1638, 0x163A, 0x163C, 0x163E, 0x1640, 0x1642, 0x1644, // Note: 69
    0x1646, 0x1648, 0x164A, 0x164C, 0x164F, 0x1651, 0x1653, 0x1655, 
    0x1657, 0x1659, 0x165C, 0x165E, 0x1660, 0x1662, 0x1664, 0x1667, // Note: 70
    0x1669, 0x166B, 0x166D, 0x166F, 0x1672, 0x1674, 0x1676, 0x1679, 
    0x167B, 0x167D, 0x167F, 0x1682, 0x1684, 0x1686, 0x1689, 0x168B, // Note: 71
    0x168D, 0x1690, 0x1692, 0x1695, 0x1697, 0x1699, 0x169C, 0x169E, 
    0x16A1, 0x16A3, 0x16A5, 0x16A8, 0x16AA, 0x16AD, 0x16AF, 0x16B2, // Note: 72
    0x16B4, 0x16B7, 0x16B9, 0x16BC, 0x16BE, 0x16C1, 0x16C3, 0x16C6, 
    0x16C9, 0x16CB, 0x16CE, 0x16D0, 0x16D3, 0x16D6, 0x16D8, 0x16DB, // Note: 73
    0x16DD, 0x16E0, 0x16E3, 0x16E5, 0x16E8, 0x16EB, 0x16ED, 0x16F0, 
    0x16F3, 0x16F6, 0x16F8, 0x16FB, 0x16FE, 0x1701, 0x1703, 0x1706, // Note: 74
    0x1709, 0x170C, 0x170F, 0x1711, 0x1714, 0x1717, 0x171A, 0x171D, 
    0x1720, 0x1723, 0x1726, 0x1729, 0x172B, 0x172E, 0x1731, 0x1734, // Note: 75
    0x1737, 0x173A, 0x173D, 0x1740, 0x1743, 0x1746, 0x1749, 0x174C, 
    0x174F, 0x1752, 0x1756, 0x1759, 0x175C, 0x175F, 0x1762, 0x1765, // Note: 76
    0x1768, 0x176B, 0x176F, 0x1772, 0x1775, 0x1778, 0x177B, 0x177F, 
    0x1782, 0x1785, 0x1788, 0x178C, 0x178F, 0x1792, 0x1795, 0x1799, // Note: 77
    0x179C, 0x179F, 0x17A3, 0x17A6, 0x17A9, 0x17AD, 0x17B0, 0x17B4, 
    0x17B7, 0x17BB, 0x17BE, 0x17C1, 0x17C5, 0x17C8, 0x17CC, 0x17CF, // Note: 78
    0x17D3, 0x17D7, 0x17DA, 0x17DE, 0x17E1, 0x17E5, 0x17E8, 0x17EC, 
    0x17F0, 0x17F3, 0x17F7, 0x17FB, 0x17FE, 0x1A01, 0x1A03, 0x1A05, // Note: 79
    0x1A07, 0x1A08, 0x1A0A, 0x1A0C, 0x1A0E, 0x1A10, 0x1A12, 0x1A14, 
    0x1A16, 0x1A18, 0x1A1A, 0x1A1C, 0x1A1E, 0x1A20, 0x1A21, 0x1A23, // Note: 80
    0x1A25, 0x1A27, 0x1A29, 0x1A2B, 0x1A2D, 0x1A2F, 0x1A31, 0x1A34, 
    0x1A36, 0x1A38, 0x1A3A, 0x1A3C, 0x1A3E, 0x1A40, 0x1A42, 0x1A44, // Note: 81
    0x1A46, 0x1A48, 0x1A4A, 0x1A4C, 0x1A4F, 0x1A51, 0x1A53, 0x1A55, 
    0x1A57, 0x1A59, 0x1A5C, 0x1A5E, 0x1A60, 0x1A62, 0x1A64, 0x1A67, // Note: 82
    0x1A69, 0x1A6B, 0x1A6D, 0x1A6F, 0x1A72, 0x1A74, 0x1A76, 0x1A79, 
    0x1A7B, 0x1A7D, 0x1A7F, 0x1A82, 0x1A84, 0x1A86, 0x1A89, 0x1A8B, // Note: 83
    0x1A8D, 0x1A90, 0x1A92, 0x1A95, 0x1A97, 0x1A99, 0x1A9C, 0x1A9E, 
    0x1AA1, 0x1AA3, 0x1AA5, 0x1AA8, 0x1AAA, 0x1AAD, 0x1AAF, 0x1AB2, // Note: 84
    0x1AB4, 0x1AB7, 0x1AB9, 0x1ABC, 0x1ABE, 0x1AC1, 0x1AC3, 0x1AC6, 
    0x1AC9, 0x1ACB, 0x1ACE, 0x1AD0, 0x1AD3, 0x1AD6, 0x1AD8, 0x1ADB, // Note: 85
    0x1ADD, 0x1AE0, 0x1AE3, 0x1AE5, 0x1AE8, 0x1AEB, 0x1AED, 0x1AF0, 
    0x1AF3, 0x1AF6, 0x1AF8, 0x1AFB, 0x1AFE, 0x1B01, 0x1B03, 0x1B06, // Note: 86
    0x1B09, 0x1B0C, 0x1B0F, 0x1B11, 0x1B14, 0x1B17, 0x1B1A, 0x1B1D, 
    0x1B20, 0x1B23, 0x1B26, 0x1B29, 0x1B2B, 0x1B2E, 0x1B31, 0x1B34, // Note: 87
    0x1B37, 0x1B3A, 0x1B3D, 0x1B40, 0x1B43, 0x1B46, 0x1B49, 0x1B4C, 
    0x1B4F, 0x1B52, 0x1B56, 0x1B59, 0x1B5C, 0x1B5F, 0x1B62, 0x1B65, // Note: 88
    0x1B68, 0x1B6B, 0x1B6F, 0x1B72, 0x1B75, 0x1B78, 0x1B7B, 0x1B7F, 
    0x1B82, 0x1B85, 0x1B88, 0x1B8C, 0x1B8F, 0x1B92, 0x1B95, 0x1B99, // Note: 89
    0x1B9C, 0x1B9F, 0x1BA3, 0x1BA6, 0x1BA9, 0x1BAD, 0x1BB0, 0x1BB4, 
    0x1BB7, 0x1BBB, 0x1BBE, 0x1BC1, 0x1BC5, 0x1BC8, 0x1BCC, 0x1BCF, // Note: 90
    0x1BD3, 0x1BD7, 0x1BDA, 0x1BDE, 0x1BE1, 0x1BE5, 0x1BE8, 0x1BEC, 
    0x1BF0, 0x1BF3, 0x1BF7, 0x1BFB, 0x1BFE, 0x1E01, 0x1E03, 0x1E05, // Note: 91
    0x1E07, 0x1E08, 0x1E0A, 0x1E0C, 0x1E0E, 0x1E10, 0x1E12, 0x1E14, 
    0x1E16, 0x1E18, 0x1E1A, 0x1E1C, 0x1E1E, 0x1E20, 0x1E21, 0x1E23, // Note: 92
    0x1E25, 0x1E27, 0x1E29, 0x1E2B, 0x1E2D, 0x1E2F, 0x1E31, 0x1E34, 
    0x1E36, 0x1E38, 0x1E3A, 0x1E3C, 0x1E3E, 0x1E40, 0x1E42, 0x1E44, // Note: 93
    0x1E46, 0x1E48, 0x1E4A, 0x1E4C, 0x1E4F, 0x1E51, 0x1E53, 0x1E55, 
    0x1E57, 0x1E59, 0x1E5C, 0x1E5E, 0x1E60, 0x1E62, 0x1E64, 0x1E67, // Note: 94
    0x1E69, 0x1E6B, 0x1E6D, 0x1E6F, 0x1E72, 0x1E74, 0x1E76, 0x1E79, 
    0x1E7B, 0x1E7D, 0x1E7F, 0x1E82, 0x1E84, 0x1E86, 0x1E89, 0x1E8B, 
    0x1E8D, 0x1E90, 0x1E92, 0x1E95, 0x1E97, 0x1E99, 0x1E9C, 0x1E9E, 
    0x1EA1, 0x1EA3, 0x1EA5, 0x1EA8, 0x1EAA, 0x1EAD, 0x1EAF, 0x1EAF, // Note: 95
};

#endif
