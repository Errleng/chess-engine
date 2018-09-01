use board;
use board::File;
use board::Piece;
use board::Rank;
use board::Side;
use board::Square;
use types::IdxVec;

pub const CAPTURE_FLAG: u32 = 0x7C000;
pub const CASTLE_FLAG: u32 = 0x1000000;
pub const PAWN_START_FLAG: u32 = 0x80000;
pub const ENPASSANT_FLAG: u32 = 0x40000;
pub const PROMOTION_FLAG: u32 = 0xF00000;

#[derive(Copy, Clone)]
pub struct Move<'a> {
    pub mv: u32,
    pub score: u32,
    pub util: &'a board::Util,
}

impl<'a> Move<'a> {
    pub fn construct(
        util: &board::Util,
        from_sq: u8,
        to_sq: u8,
        capture: u8,
        promotion: u8,
        flag: u32,
    ) -> Move {
        Move {
            mv: (from_sq as u32)
                | ((to_sq as u32) << 7)
                | ((capture as u32) << 14)
                | ((promotion as u32) << 20)
                | flag,
            score: 0,
            util: util,
        }
    }
    pub fn init(util: &board::Util) -> Move {
        Move {
            mv: 0,
            score: 0,
            util: util,
        }
    }

    pub fn to_string(&self) -> String {
        let file_from = self.util.files[self.from_sq()];
        let rank_from = self.util.ranks[self.from_sq()];
        let file_to = self.util.files[self.to_sq()];
        let rank_to = self.util.ranks[self.to_sq()];

        let promoted = self.promoted();

        if promoted != 0 {
            let mut pce_char = 'q';
            if self.util.is_knight[promoted] {
                pce_char = 'n';
            } else if self.util.is_rook_queen[promoted] && !self.util.is_bishop_queen[promoted] {
                pce_char = 'r';
            } else if !self.util.is_rook_queen[promoted] && self.util.is_bishop_queen[promoted] {
                pce_char = 'b';
            }
            format!(
                "{}{}{}{}{}",
                ('a' as u8 + file_from) as char,
                ('1' as u8 + rank_from) as char,
                ('a' as u8 + file_to) as char,
                ('1' as u8 + rank_to) as char,
                pce_char
            )
        } else {
            format!(
                "{}{}{}{}",
                ('a' as u8 + file_from) as char,
                ('1' as u8 + rank_from) as char,
                ('a' as u8 + file_to) as char,
                ('1' as u8 + rank_to) as char
            )
        }
    }

    pub fn from_sq(&self) -> u32 {
        self.mv & 0x7F
    }
    pub fn to_sq(&self) -> u32 {
        self.mv >> 7 & 0x7F
    }
    pub fn captured(&self) -> u32 {
        self.mv >> 14 & 0xF
    }
    pub fn promoted(&self) -> u32 {
        self.mv >> 20 & 0xF
    }

    pub fn is_capture(&self) -> bool {
        self.mv & CAPTURE_FLAG != 0
    }
    pub fn is_castle(&self) -> bool {
        self.mv & CASTLE_FLAG != 0
    }
    pub fn is_pawn_start(&self) -> bool {
        self.mv & PAWN_START_FLAG != 0
    }
    pub fn is_enpassant(&self) -> bool {
        self.mv & ENPASSANT_FLAG != 0
    }
    pub fn is_promotion(&self) -> bool {
        self.mv & PROMOTION_FLAG != 0
    }

    pub fn set_is_capture(&mut self) {
        self.mv |= CAPTURE_FLAG;
    }
    pub fn set_castle(&mut self) {
        self.mv |= CASTLE_FLAG;
    }
    pub fn set_pawn_start(&mut self) {
        self.mv |= PAWN_START_FLAG;
    }
    pub fn set_enpassant(&mut self) {
        self.mv |= ENPASSANT_FLAG;
    }
    pub fn set_is_promotion(&mut self) {
        self.mv |= PROMOTION_FLAG;
    }
}

#[derive(Copy, Clone)]
pub struct PastMove {
    pub mv: u8,
    pub castling_status: u8,
    pub enpassant: u8,
    pub fifty_moves: u8,
    pub key: u64,
}

impl Default for PastMove {
    fn default() -> PastMove {
        PastMove {
            mv: 0,
            castling_status: 0,
            enpassant: 0,
            fifty_moves: 0,
            key: 0,
        }
    }
}

pub struct MoveList<'a> {
    pub moves: IdxVec<Move<'a>>,
    pub count: u8,
}

impl<'a> MoveList<'a> {
    pub fn init(util: &'a board::Util) -> MoveList<'a> {
        MoveList {
            moves: IdxVec(vec![Move::init(util); board::MAX_POS_MOVES]),
            count: 0,
        }
    }
    pub fn print(&self) {
        for i in 0..self.count {
            let mv = self.moves[i].to_string();
            let score = self.moves[i].score;
            println!("Move {} = {}, Score = {}", i + 1, mv, score);
        }
        println!("MoveList count = {}", self.count);
    }
}
