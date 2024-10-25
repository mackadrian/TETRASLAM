#ifndef BITMAPS_H
#define BITMAPS_H
#include "types.h"

/*NOTE: Temporary use of .h header file for easier test calls for stage 2.*/

const UINT16 tile[16] = {
	0xffff,
	0xe007,
	0xf00f,
	0xb81d,
	0x9c39,
	0x8e71,
	0x87e1,
	0x83c1,
	0x83c1,
	0x87e1,
	0x8e71,
	0x9c39,
	0xb81d,
	0xf00f,
	0xe007,
	0xffff};

const UINT16 I_piece[61] = {
	0xffff,
	0xe007,
	0xf00f,
	0xb81d,
	0x9c39,
	0x8e71,
	0x87e1,
	0x83c1,
	0x83c1,
	0x87e1,
	0x8e71,
	0x9c39,
	0xb81d,
	0xf00f,
	0xe007,
	0xffff,
	0xe007,
	0xf00f,
	0xb81d,
	0x9c39,
	0x8e71,
	0x87e1,
	0x83c1,
	0x83c1,
	0x87e1,
	0x8e71,
	0x9c39,
	0xb81d,
	0xf00f,
	0xe007,
	0xffff,
	0xe007,
	0xf00f,
	0xb81d,
	0x9c39,
	0x8e71,
	0x87e1,
	0x83c1,
	0x83c1,
	0x87e1,
	0x8e71,
	0x9c39,
	0xb81d,
	0xf00f,
	0xe007,
	0xffff,
	0xe007,
	0xf00f,
	0xb81d,
	0x9c39,
	0x8e71,
	0x87e1,
	0x83c1,
	0x83c1,
	0x87e1,
	0x8e71,
	0x9c39,
	0xb81d,
	0xf00f,
	0xe007,
	0xffff};

const UINT16 J_piece[92] = {
	0x0001, 0xfffe,
	0x0001, 0xc00e,
	0x0001, 0xe01e,
	0x0001, 0x703a,
	0x0001, 0x3872,
	0x0001, 0x1ce2,
	0x0001, 0x0fc2,
	0x0001, 0x0782,
	0x0001, 0x0782,
	0x0001, 0x0fc2,
	0x0001, 0x1ce2,
	0x0001, 0x3872,
	0x0001, 0x703a,
	0x0001, 0xe01e,
	0x0001, 0xc00e,
	0x0001, 0xfffe,
	0x0001, 0xc00e,
	0x0001, 0xe01e,
	0x0001, 0x703a,
	0x0001, 0x3872,
	0x0001, 0x1ce2,
	0x0001, 0x0fc2,
	0x0001, 0x0782,
	0x0001, 0x0782,
	0x0001, 0x0fc2,
	0x0001, 0x1ce2,
	0x0001, 0x3872,
	0x0001, 0x703a,
	0x0001, 0xe01e,
	0x0001, 0xc00e,
	0xffff, 0xfffe,
	0xe007, 0xc00e,
	0xf00f, 0xe01e,
	0xb81d, 0x703a,
	0x9c39, 0x3872,
	0x8e71, 0x1ce2,
	0x87e1, 0x0fc2,
	0x83c1, 0x0782,
	0x83c1, 0x0782,
	0x87e1, 0x0fc2,
	0x8e71, 0x1ce2,
	0x9c39, 0x3872,
	0xb81d, 0x703a,
	0xf00f, 0xe01e,
	0xe007, 0xc00e,
	0xffff, 0xfffe};

const UINT16 L_piece[92] = {
	0xffff, 0x0000,
	0xe007, 0x0000,
	0xf00f, 0x0000,
	0xb81d, 0x0000,
	0x9c39, 0x0000,
	0x8e71, 0x0000,
	0x87e1, 0x0000,
	0x83c1, 0x0000,
	0x83c1, 0x0000,
	0x87e1, 0x0000,
	0x8e71, 0x0000,
	0x9c39, 0x0000,
	0xb81d, 0x0000,
	0xf00f, 0x0000,
	0xe007, 0x0000,
	0xffff, 0x0000,
	0xe007, 0x0000,
	0xf00f, 0x0000,
	0xb81d, 0x0000,
	0x9c39, 0x0000,
	0x8e71, 0x0000,
	0x87e1, 0x0000,
	0x83c1, 0x0000,
	0x83c1, 0x0000,
	0x87e1, 0x0000,
	0x8e71, 0x0000,
	0x9c39, 0x0000,
	0xb81d, 0x0000,
	0xf00f, 0x0000,
	0xe007, 0x0000,
	0xffff, 0xfffe,
	0xe007, 0xc00e,
	0xf00f, 0xe01e,
	0xb81d, 0x703a,
	0x9c39, 0x3872,
	0x8e71, 0x1ce2,
	0x87e1, 0x0fc2,
	0x83c1, 0x0782,
	0x83c1, 0x0782,
	0x87e1, 0x0fc2,
	0x8e71, 0x1ce2,
	0x9c39, 0x3872,
	0xb81d, 0x703a,
	0xf00f, 0xe01e,
	0xe007, 0xc00e,
	0xffff, 0xfffe};

const UINT16 O_piece[62] = {
	0xffff, 0xfffe,
	0xe007, 0xc00e,
	0xf00f, 0xe01e,
	0xb81d, 0x703a,
	0x9c39, 0x3872,
	0x8e71, 0x1ce2,
	0x87e1, 0x0fc2,
	0x83c1, 0x0782,
	0x83c1, 0x0782,
	0x87e1, 0x0fc2,
	0x8e71, 0x1ce2,
	0x9c39, 0x3872,
	0xb81d, 0x703a,
	0xf00f, 0xe01e,
	0xe007, 0xc00e,
	0xffff, 0xfffe,
	0xe007, 0xc00e,
	0xf00f, 0xe01e,
	0xb81d, 0x703a,
	0x9c39, 0x3872,
	0x8e71, 0x1ce2,
	0x87e1, 0x0fc2,
	0x83c1, 0x0782,
	0x83c1, 0x0782,
	0x87e1, 0x0fc2,
	0x8e71, 0x1ce2,
	0x9c39, 0x3872,
	0xb81d, 0x703a,
	0xf00f, 0xe01e,
	0xe007, 0xc00e,
	0xffff, 0xfffe};

const UINT16 S_piece[93] = {
	0x0001, 0xffff, 0xfffc,
	0x0001, 0xc00f, 0x801c,
	0x0001, 0xe01f, 0xc03c,
	0x0001, 0x703a, 0xe074,
	0x0001, 0x3872, 0x70e4,
	0x0001, 0x1ce2, 0x39c4,
	0x0001, 0x0fc2, 0x1f84,
	0x0001, 0x0782, 0x0f04,
	0x0001, 0x0782, 0x0f04,
	0x0001, 0x0fc2, 0x1f84,
	0x0001, 0x1ce2, 0x39c4,
	0x0001, 0x3872, 0x70e4,
	0x0001, 0x703a, 0xe074,
	0x0001, 0xe01f, 0xc03c,
	0x0001, 0xc00f, 0x801c,
	0xffff, 0xffff, 0xfffc,
	0xe007, 0xc00e, 0x0000,
	0xf00f, 0xe01e, 0x0000,
	0xb81d, 0x703a, 0x0000,
	0x9c39, 0x3872, 0x0000,
	0x8e71, 0x1ce2, 0x0000,
	0x87e1, 0x0fc2, 0x0000,
	0x83c1, 0x0782, 0x0000,
	0x83c1, 0x0782, 0x0000,
	0x87e1, 0x0fc2, 0x0000,
	0x8e71, 0x1ce2, 0x0000,
	0x9c39, 0x3872, 0x0000,
	0xb81d, 0x703a, 0x0000,
	0xf00f, 0xe01e, 0x0000,
	0xe007, 0xc00e, 0x0000,
	0xffff, 0xfffe, 0x0000};

const UINT16 T_piece[93] = {
	0xffff, 0xffff, 0xfffc,
	0xe007, 0xc00f, 0x801c,
	0xf00f, 0xe01f, 0xc03c,
	0xb81d, 0x703a, 0xe074,
	0x9c39, 0x3872, 0x70e4,
	0x8e71, 0x1ce2, 0x39c4,
	0x87e1, 0x0fc2, 0x1f84,
	0x83c1, 0x0782, 0x0f04,
	0x83c1, 0x0782, 0x0f04,
	0x87e1, 0x0fc2, 0x1f84,
	0x8e71, 0x1ce2, 0x39c4,
	0x9c39, 0x3872, 0x70e4,
	0xb81d, 0x703a, 0xe074,
	0xf00f, 0xe01f, 0xc03c,
	0xe007, 0xc00f, 0x801c,
	0xffff, 0xffff, 0xfffc,
	0x0001, 0xc00e, 0x0000,
	0x0001, 0xe01e, 0x0000,
	0x0001, 0x703a, 0x0000,
	0x0001, 0x3872, 0x0000,
	0x0001, 0x1ce2, 0x0000,
	0x0001, 0x0fc2, 0x0000,
	0x0001, 0x0782, 0x0000,
	0x0001, 0x0782, 0x0000,
	0x0001, 0x0fc2, 0x0000,
	0x0001, 0x1ce2, 0x0000,
	0x0001, 0x3872, 0x0000,
	0x0001, 0x703a, 0x0000,
	0x0001, 0xe01e, 0x0000,
	0x0001, 0xc00e, 0x0000,
	0x0001, 0xfffe, 0x0000};

const UINT16 Z_piece[93] = {
	0xffff, 0xfffe, 0x0000,
	0xe007, 0xc00e, 0x0000,
	0xf00f, 0xe01e, 0x0000,
	0xb81d, 0x703a, 0x0000,
	0x9c39, 0x3872, 0x0000,
	0x8e71, 0x1ce2, 0x0000,
	0x87e1, 0x0fc2, 0x0000,
	0x83c1, 0x0782, 0x0000,
	0x83c1, 0x0782, 0x0000,
	0x87e1, 0x0fc2, 0x0000,
	0x8e71, 0x1ce2, 0x0000,
	0x9c39, 0x3872, 0x0000,
	0xb81d, 0x703a, 0x0000,
	0xf00f, 0xe01e, 0x0000,
	0xe007, 0xc00e, 0x0000,
	0xffff, 0xffff, 0xfffc,
	0x0001, 0xc00f, 0x801c,
	0x0001, 0xe01f, 0xc03c,
	0x0001, 0x703a, 0xe074,
	0x0001, 0x3872, 0x70e4,
	0x0001, 0x1ce2, 0x39c4,
	0x0001, 0x0fc2, 0x1f84,
	0x0001, 0x0782, 0x0f04,
	0x0001, 0x0782, 0x0f04,
	0x0001, 0x0fc2, 0x1f84,
	0x0001, 0x1ce2, 0x39c4,
	0x0001, 0x3872, 0x70e4,
	0x0001, 0x703a, 0xe074,
	0x0001, 0xe01f, 0xc03c,
	0x0001, 0xc00f, 0x801c,
	0x0001, 0xffff, 0xfffc};

const UINT16 playing_field[3030] = {

	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xff80,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xff80,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xff80,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xff80,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xff80,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xff80,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xff80,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xff80,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xff80,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xff80,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xff80,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xff80,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xff80,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xff80,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xff80,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xff80,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xff80,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xff80,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xff80,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xff80,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0x8000, 0x8001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0080,
	0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xff80};

#endif