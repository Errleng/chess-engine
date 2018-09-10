use position;
use rand;
use types::FlattenedIdxVec;
use types::IdxVec;

pub const NUM_SQUARES: usize = 64;
pub const REPR_NUM_SQUARES: usize = 120;
pub const MAX_MOVES: usize = 2048;
pub const MAX_POS_MOVES: usize = 256;

pub mod Side {
    pub const WHITE: u8 = 0;
    pub const BLACK: u8 = 1;
    pub const BOTH: u8 = 2;
}

pub mod Piece {
    pub const EMPTY: u8 = 0;
    pub const WP: u8 = 1;
    pub const WN: u8 = 2;
    pub const WB: u8 = 3;
    pub const WR: u8 = 4;
    pub const WQ: u8 = 5;
    pub const WK: u8 = 6;
    pub const BP: u8 = 7;
    pub const BN: u8 = 8;
    pub const BB: u8 = 9;
    pub const BR: u8 = 10;
    pub const BQ: u8 = 11;
    pub const BK: u8 = 12;
}

pub mod Rank {
    pub const RANK_1: u8 = 0;
    pub const RANK_2: u8 = 1;
    pub const RANK_3: u8 = 2;
    pub const RANK_4: u8 = 3;
    pub const RANK_5: u8 = 4;
    pub const RANK_6: u8 = 5;
    pub const RANK_7: u8 = 6;
    pub const RANK_8: u8 = 7;
    pub const None: u8 = 8;
}

pub mod File {
    pub const FILE_A: u8 = 0;
    pub const FILE_B: u8 = 1;
    pub const FILE_C: u8 = 2;
    pub const FILE_D: u8 = 3;
    pub const FILE_E: u8 = 4;
    pub const FILE_F: u8 = 5;
    pub const FILE_G: u8 = 6;
    pub const FILE_H: u8 = 7;
    pub const None: u8 = 8;
}

pub mod Square {
    pub const A1: u8 = 21;
    pub const B1: u8 = 22;
    pub const C1: u8 = 23;
    pub const D1: u8 = 24;
    pub const E1: u8 = 25;
    pub const F1: u8 = 26;
    pub const G1: u8 = 27;
    pub const H1: u8 = 28;
    pub const A2: u8 = 31;
    pub const B2: u8 = 32;
    pub const C2: u8 = 33;
    pub const D2: u8 = 34;
    pub const E2: u8 = 35;
    pub const F2: u8 = 36;
    pub const G2: u8 = 37;
    pub const H2: u8 = 38;
    pub const A3: u8 = 41;
    pub const B3: u8 = 42;
    pub const C3: u8 = 43;
    pub const D3: u8 = 44;
    pub const E3: u8 = 45;
    pub const F3: u8 = 46;
    pub const G3: u8 = 47;
    pub const H3: u8 = 48;
    pub const A4: u8 = 51;
    pub const B4: u8 = 52;
    pub const C4: u8 = 53;
    pub const D4: u8 = 54;
    pub const E4: u8 = 55;
    pub const F4: u8 = 56;
    pub const G4: u8 = 57;
    pub const H4: u8 = 58;
    pub const A5: u8 = 61;
    pub const B5: u8 = 62;
    pub const C5: u8 = 63;
    pub const D5: u8 = 64;
    pub const E5: u8 = 65;
    pub const F5: u8 = 66;
    pub const G5: u8 = 67;
    pub const H5: u8 = 68;
    pub const A6: u8 = 71;
    pub const B6: u8 = 72;
    pub const C6: u8 = 73;
    pub const D6: u8 = 74;
    pub const E6: u8 = 75;
    pub const F6: u8 = 76;
    pub const G6: u8 = 77;
    pub const H6: u8 = 78;
    pub const A7: u8 = 81;
    pub const B7: u8 = 82;
    pub const C7: u8 = 83;
    pub const D7: u8 = 84;
    pub const E7: u8 = 85;
    pub const F7: u8 = 86;
    pub const G7: u8 = 87;
    pub const H7: u8 = 88;
    pub const A8: u8 = 91;
    pub const B8: u8 = 92;
    pub const C8: u8 = 93;
    pub const D8: u8 = 94;
    pub const E8: u8 = 95;
    pub const F8: u8 = 96;
    pub const G8: u8 = 97;
    pub const H8: u8 = 98;
    pub const NONE: u8 = 99;
    pub const OFFBOARD: u8 = 100;
}

pub mod Castling {
    pub const WK: u8 = 1;
    pub const WQ: u8 = 2;
    pub const BK: u8 = 4;
    pub const BQ: u8 = 8;
}

//enusize! {
//#[repr(usize)]
//#[derive(Copy, Clone)]
//pusize enum Side {
//    White,
//    Black,
//    Both,
//}
//}

//enusize! {
//#[repr(usize)]
//pusize enum Piece {
//    Empty,
//    WP,
//    WN,
//    WB,
//    WR,
//    WQ,
//    WK,
//    BP,
//    BN,
//    BB,
//    BR,
//    BQ,
//    BK,
//}
//}

//enum_from_primitive! {
//#[repr(u8)]
//pub enum File {
//    FileA,
//    FileB,
//    FileC,
//    FileD,
//    FileE,
//    FileF,
//    FileG,
//    FileH,
//    None,
//}

//}
//enum_from_primitive! {
//#[repr(u8)]
//pub enum Rank {
//    Rank1,
//    Rank2,
//    Rank3,
//    Rank4,
//    Rank5,
//    Rank6,
//    Rank7,
//    Rank8,
//    None,
//}

//}
//enum_from_primitive! {
//#[repr(u8)]
//pub enum Square {
//    A1 = 21,
//    B1,
//    C1,
//    D1,
//    E1,
//    F1,
//    G1,
//    H1,
//    A2 = 31,
//    B2,
//    C2,
//    D2,
//    E2,
//    F2,
//    G2,
//    H2,
//    A3 = 41,
//    B3,
//    C3,
//    D3,
//    E3,
//    F3,
//    G3,
//    H3,
//    A4 = 51,
//    B4,
//    C4,
//    D4,
//    E4,
//    F4,
//    G4,
//    H4,
//    A5 = 61,
//    B5,
//    C5,
//    D5,
//    E5,
//    F5,
//    G5,
//    H5,
//    A6 = 71,
//    B6,
//    C6,
//    D6,
//    E6,
//    F6,
//    G6,
//    H6,
//    A7 = 81,
//    B7,
//    C7,
//    D7,
//    E7,
//    F7,
//    G7,
//    H7,
//    A8 = 91,
//    B8,
//    C8,
//    D8,
//    E8,
//    F8,
//    G8,
//    H8,
//    None,
//    OffBoard,
//}

//}
//enum_from_primitive! {
//#[repr(u8)]
//pub enum Castling {
//    WK = 1;
//    WQ = 2,
//    BK = 4,
//    BQ = 8,
//}
//}

// Singleton? Global variables?
pub struct Util {
    // square conversion tables
    pub sq64_to_sq120: IdxVec<u8>,
    pub sq120_to_sq64: IdxVec<u8>,

    // magic table
    pub bit_table: IdxVec<u8>,

    // bitmasks
    pub set_masks: IdxVec<u64>,
    pub clear_masks: IdxVec<u64>,
    pub piece_keys: FlattenedIdxVec<u64>,

    // hashkeys
    pub side_key: u64,
    pub castle_keys: IdxVec<u64>,

    // ascii board representation
    pub piece_chars: IdxVec<char>,
    pub side_chars: IdxVec<char>,
    pub rank_chars: IdxVec<char>,
    pub file_chars: IdxVec<char>,

    // piece type
    pub is_big_piece: IdxVec<bool>,
    pub is_major_piece: IdxVec<bool>,
    pub is_minor_piece: IdxVec<bool>,
    pub piece_values: IdxVec<u32>,
    pub piece_colours: IdxVec<u8>,

    // square number to file and rank
    pub ranks: IdxVec<u8>,
    pub files: IdxVec<u8>,

    // piece checking
    pub is_pawn: IdxVec<bool>,
    pub is_knight: IdxVec<bool>,
    pub is_king: IdxVec<bool>,
    pub is_rook_queen: IdxVec<bool>,
    pub is_bishop_queen: IdxVec<bool>,

    // piece directions
    pub piece_dir: FlattenedIdxVec<i8>,
    pub num_dir: IdxVec<u8>,
    // pub knight_dir: IdxVec<i8>,
    // pub bishop_dir: IdxVec<i8>,
    // pub rook_dir: IdxVec<i8>,
    // pub king_queen_dir: IdxVec<i8>,

    // promotions
    pub white_promotions: IdxVec<u8>,
    pub black_promotions: IdxVec<u8>,

    // sliding attack or not
    pub is_sliding_piece: IdxVec<bool>,
    pub sliding: IdxVec<u8>,

    // castling permission
    pub castling_perm: IdxVec<u8>, // Rook, King movements for from_sq
}

impl Util {
    pub fn is_square_valid(&self, sq: u8) -> bool {
        self.files[sq] != Square::OFFBOARD
    }
    pub fn is_side_valid(&self, side: u8) -> bool {
        side == Side::WHITE || side == Side::BLACK
    }
    pub fn is_fr_valid(&self, fr: u8) -> bool {
        fr >= 0 && fr <= 7
    }
    pub fn is_piece(&self, fr: u8) -> bool {
        fr >= 0 && fr <= 7
    }
    pub fn is_piece_valid(&self, pce: u8) -> bool {
        pce >= Piece::WP && pce <= Piece::BK
    }
    pub fn sq_to_string(&self, sq: u8) -> String {
        let file = self.files[sq];
        let rank = self.ranks[sq];
        format!(
            "{}{}",
            (file + 'a' as u8) as char,
            (rank + '1' as u8) as char
        )
    }
    pub fn fr_to_sq(&self, file: u8, rank: u8) -> u8 {
        ((21 + file) + (rank * 10))
    }

    pub fn init(&mut self) {
        self.init_sq_conv();
        self.init_bitmasks();
        self.init_zobrist_keys();
        self.init_files_ranks();
    }

    fn init_sq_conv(&mut self) {
        let mut sq;
        let mut sq64 = 0;
        for rank in Rank::RANK_1..=Rank::RANK_8 {
            for file in File::FILE_A..=File::FILE_H {
                sq = self.fr_to_sq(file, rank);
                self.sq64_to_sq120[sq64] = sq;
                self.sq120_to_sq64[sq] = sq64;
                sq64 += 1;
            }
        }
    }

    fn init_bitmasks(&mut self) {
        for i in 0..NUM_SQUARES {
            self.set_masks[i] |= 1u64 << i;
            self.clear_masks[i] = !self.set_masks[i]; // ! = bitwise OR logical complement
        }
    }

    fn init_zobrist_keys(&mut self) {
        self.side_key = rand::random::<u64>();
        for i in 0..16 {
            self.castle_keys[i] = rand::random::<u64>();
        }
        for i in 0..13 {
            for j in 0..REPR_NUM_SQUARES {
                self.piece_keys[(i, j)] = rand::random::<u64>();
            }
        }
    }

    fn init_files_ranks(&mut self) {
        let mut sq;
        for rank in Rank::RANK_1..=Rank::RANK_8 {
            for file in File::FILE_A..=File::FILE_H {
                sq = self.fr_to_sq(file, rank);
                self.ranks[sq] = rank;
                self.files[sq] = file;
            }
        }
    }

    pub fn gen_pos_key(&self, pos: &position::Position) -> u64 {
        let mut key = 0;
        let mut piece;

        for sq in 0..REPR_NUM_SQUARES {
            piece = pos.pieces[sq];
            if piece != Square::NONE && piece != Square::OFFBOARD && piece != Piece::EMPTY {
                debug_assert!(piece >= Piece::WP && piece <= Piece::BK);
                key ^= self.piece_keys[(piece, sq)];
            }
        }

        if pos.side == Side::WHITE {
            key ^= self.side_key;
        }

        if pos.enpassant != Square::NONE {
            debug_assert!(pos.enpassant >= 0 && pos.enpassant < REPR_NUM_SQUARES as u8);
            key ^= self.piece_keys[(Piece::EMPTY, pos.enpassant)];
        }

        debug_assert!(pos.castling >= 0 && pos.castling <= 15);
        key ^= self.castle_keys[pos.castling];
        key
    }
}

impl Default for Util {
    fn default() -> Util {
        Util {
            sq64_to_sq120: IdxVec(vec![120; NUM_SQUARES]),
            sq120_to_sq64: IdxVec(vec![65; REPR_NUM_SQUARES]),
            bit_table: IdxVec(vec![
                63, 30, 3, 32, 25, 41, 22, 33, 15, 50, 42, 13, 11, 53, 19, 34, 61, 29, 2, 51, 21,
                43, 45, 10, 18, 47, 1, 54, 9, 57, 0, 35, 62, 31, 40, 4, 49, 5, 52, 26, 60, 6, 23,
                44, 46, 27, 56, 16, 7, 39, 48, 24, 59, 14, 12, 55, 38, 28, 58, 20, 37, 17, 36, 8,
            ]),
            set_masks: IdxVec(vec![0; NUM_SQUARES]),
            clear_masks: IdxVec(vec![0; NUM_SQUARES]),
            piece_keys: FlattenedIdxVec {
                row: REPR_NUM_SQUARES,
                col: 13,
                cont: vec![0; REPR_NUM_SQUARES * 13],
            },
            side_key: 0,
            castle_keys: IdxVec(vec![0; 16]),
            piece_chars: IdxVec(vec![
                '.', 'P', 'N', 'B', 'R', 'Q', 'K', 'p', 'n', 'b', 'r', 'q', 'k',
            ]),
            side_chars: IdxVec(vec!['w', 'b', '-']),
            rank_chars: IdxVec(vec!['1', '2', '3', '4', '5', '6', '7', '8']),
            file_chars: IdxVec(vec!['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h']),
            is_big_piece: IdxVec(vec![
                false, false, true, true, true, true, true, false, true, true, true, true, true,
            ]),
            is_major_piece: IdxVec(vec![
                false, false, false, false, true, true, true, false, false, false, true, true, true,
            ]),
            is_minor_piece: IdxVec(vec![
                false, false, true, true, false, false, false, false, true, true, false, false,
                false,
            ]),
            piece_values: IdxVec(vec![
                0, 100, 325, 325, 550, 1000, 50000, 100, 325, 325, 550, 1000, 50000,
            ]),
            piece_colours: IdxVec(vec![
                Side::BOTH,
                Side::WHITE,
                Side::WHITE,
                Side::WHITE,
                Side::WHITE,
                Side::WHITE,
                Side::WHITE,
                Side::BLACK,
                Side::BLACK,
                Side::BLACK,
                Side::BLACK,
                Side::BLACK,
                Side::BLACK,
            ]),
            ranks: IdxVec(vec![Square::OFFBOARD; REPR_NUM_SQUARES]),
            files: IdxVec(vec![Square::OFFBOARD; REPR_NUM_SQUARES]),
            is_pawn: IdxVec(vec![
                false, true, false, false, false, false, false, true, false, false, false, false,
                false,
            ]),
            is_knight: IdxVec(vec![
                false, false, true, false, false, false, false, false, true, false, false, false,
                false,
            ]),
            is_king: IdxVec(vec![
                false, false, false, false, false, false, true, false, false, false, false, false,
                true,
            ]),
            is_rook_queen: IdxVec(vec![
                false, false, false, false, true, true, false, false, false, false, true, true,
                false,
            ]),
            is_bishop_queen: IdxVec(vec![
                false, false, false, true, false, true, false, false, false, true, false, true,
                false,
            ]),
            piece_dir: FlattenedIdxVec {
                row: 13,
                col: 8,
                cont: vec![
                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -8, -19, -21, -12, 8, 19, 21,
                    12, -9, -11, 11, 9, 0, 0, 0, 0, -1, -10, 1, 10, 0, 0, 0, 0, -1, -10, 1, 10, -9,
                    -11, 11, 9, -1, -10, 1, 10, -9, -11, 11, 9, 0, 0, 0, 0, 0, 0, 0, 0, -8, -19,
                    -21, -12, 8, 19, 21, 12, -9, -11, 11, 9, 0, 0, 0, 0, -1, -10, 1, 10, 0, 0, 0,
                    0, -1, -10, 1, 10, -9, -11, 11, 9, -1, -10, 1, 10, -9, -11, 11, 9,
                ],
            },
            // knight_dir: IdxVec(vec![-8, -19, -21, -12, 8, 19, 21, 12]),
            // bishop_dir: IdxVec(vec![-9, -11, 11, 9]),
            // rook_dir: IdxVec(vec![-1, -10, 1, 10]),
            // king_queen_dir: IdxVec(vec![-1, -10, 1, 10, -9, -11, 11, 9]),
            num_dir: IdxVec(vec![0, 0, 8, 4, 4, 8, 8, 0, 8, 4, 4, 8, 8]),
            white_promotions: IdxVec(vec![Piece::WQ, Piece::WR, Piece::WB, Piece::WN]),
            black_promotions: IdxVec(vec![Piece::BQ, Piece::BR, Piece::BB, Piece::BN]),
            is_sliding_piece: IdxVec(vec![
                false, false, false, true, true, true, false, false, false, true, true, true, false,
            ]),
            sliding: IdxVec(vec![
                Piece::WB,
                Piece::WR,
                Piece::WQ,
                Piece::WN,
                Piece::WK,
                Piece::BB,
                Piece::BR,
                Piece::BQ,
                Piece::BN,
                Piece::BK,
            ]),
            castling_perm: IdxVec(vec![
                15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
                13, 15, 15, 15, 12, 15, 15, 14, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
                15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
                15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
                15, 15, 15, 15, 15, 15, 15, 7, 15, 15, 15, 3, 15, 15, 11, 15, 15, 15, 15, 15, 15,
                15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
            ]),
        }
    }
}
