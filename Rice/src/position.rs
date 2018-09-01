use bitboard;
use board;
use board::Castling;
use board::File;
use board::Piece;
use board::Rank;
use board::Side;
use board::Square;
use board::Util;
use moves;
use moves::Move;
use types::IdxVec;

#[derive(Clone)]
pub struct Position<'a> {
    //    pub side: u8,
//    pub enpassant: u8,
//    pub fifty_moves: u8,
//    pub ply: u8,
//    pub hist_ply: u8,
//    pub castling: u8,
//    pub material: [u32; 2],
//    pub key: u64,

//    pub pieces: [u8; board::REPR_NUM_SQUARES],
//    pub piece_count: [u8; 13],
//    pub king_squares: [u8; 2],
//    pub big_pieces: [u8; 2],
//    pub major_pieces: [u8; 2],
//    pub minor_pieces: [u8; 2],
//    pub pawns: [bitboard::BitBoard; 3],
//    pub piece_list: [[u8; 10]; 13],

    //    pub history: [Option<PastMove>; board::MAX_MOVES],
//    pub bb: bitboard::BitBoard,
    pub side: u8,
    pub enpassant: u8,
    pub fifty_moves: u8,
    pub ply: u8,
    pub hist_ply: u8,
    pub castling: u8,
    pub material: IdxVec<u32>,
    pub key: u64,

    pub pieces: IdxVec<u8>,
    pub piece_count: IdxVec<u8>,
    pub king_squares: IdxVec<u8>,
    pub big_pieces: IdxVec<u8>,
    pub major_pieces: IdxVec<u8>,
    pub minor_pieces: IdxVec<u8>,
    pub pawns: IdxVec<bitboard::BitBoard<'a>>,
    pub piece_list: IdxVec<IdxVec<u8>>,

    pub history: IdxVec<moves::PastMove>,
    pub bb: bitboard::BitBoard<'a>,
    pub util: &'a Util,
}

impl<'a> Position<'a> {
    pub fn init(util: &'a Util) -> Position {
        Position {
            side: 0,
            enpassant: 0,
            fifty_moves: 0,
            ply: 0,
            hist_ply: 0,
            castling: 0,
            material: IdxVec(vec![0; 2]),
            key: 0,

            pieces: IdxVec(vec![0; board::REPR_NUM_SQUARES]),
            piece_count: IdxVec(vec![0; 13]),
            king_squares: IdxVec(vec![0; 2]),
            big_pieces: IdxVec(vec![0; 2]),
            major_pieces: IdxVec(vec![0; 2]),
            minor_pieces: IdxVec(vec![0; 2]),
            pawns: IdxVec(vec![bitboard::BitBoard::init(util); 3]),
            piece_list: IdxVec(vec![IdxVec(vec![0; 10]); 13]),

            history: IdxVec(vec![Default::default(); board::MAX_MOVES]),
            bb: bitboard::BitBoard::init(util),
            util: util,
        }
    }

    pub fn gen_moves(&self, mv_list: &mut moves::MoveList, side: u8) {
        debug_assert!(self.check_board());
        mv_list.count = 0;

        let side_pawn;
        let pawn_offsets: [i8; 3];
        let opposing_side;
        let pawn_starting_rank;
        let sliding_start_pce;
        let sliding_end_pce;
        let non_sliding_start_pce;
        let non_sliding_end_pce;

        if side == Side::WHITE {
            side_pawn = Piece::WP;
            pawn_offsets = [10, 11, 9];
            opposing_side = Side::BLACK;
            pawn_starting_rank = Rank::RANK_2;
            sliding_start_pce = 0;
            sliding_end_pce = 3;
            non_sliding_start_pce = 3;
            non_sliding_end_pce = 5;

            if self.castling & Castling::WK != 0 {
                if self.pieces[Square::F1] == Piece::EMPTs
                    && self.pieces[Square::G1] == Piece::EMPTs
                {
                    if !self.sq_attacked(Square::E1 as i8, Side::BLACK)
                        && !self.sq_attacked(Square::F1 as i8, Side::BLACK)
                    {
                        self.add_quiet_move(
                            Move::construct(
                                self.util,
                                Square::E1,
                                Square::G1,
                                Piece::EMPTs,
                                Piece::EMPTs,
                                moves::CASTLE_FLAG,
                            ),
                            mv_list,
                        );
                        //println!("WK castling");
                    }
                }
            }
            if self.castling & Castling::WQ != 0 {
                if self.pieces[Square::D1] == Piece::EMPTs
                    && self.pieces[Square::C1] == Piece::EMPTs
                    && self.pieces[Square::B1] == Piece::EMPTs
                {
                    if !self.sq_attacked(Square::E1 as i8, Side::BLACK)
                        && !self.sq_attacked(Square::D1 as i8, Side::BLACK)
                    {
                        self.add_quiet_move(
                            Move::construct(
                                self.util,
                                Square::E1,
                                Square::C1,
                                Piece::EMPTs,
                                Piece::EMPTs,
                                moves::CASTLE_FLAG,
                            ),
                            mv_list,
                        );
                        //println!("WQ castling");
                    }
                }
            }
        } else if side == Side::BLACK {
            side_pawn = Piece::BP;
            pawn_offsets = [-10, -11, -9];
            opposing_side = Side::WHITE;
            pawn_starting_rank = Rank::RANK_7;
            sliding_start_pce = 5;
            sliding_end_pce = 8;
            non_sliding_start_pce = 8;
            non_sliding_end_pce = 10;

            if self.castling & Castling::BK != 0 {
                if self.pieces[Square::F8] == Piece::EMPTs
                    && self.pieces[Square::G8] == Piece::EMPTs
                {
                    if !self.sq_attacked(Square::E8 as i8, Side::WHITE)
                        && !self.sq_attacked(Square::F8 as i8, Side::WHITE)
                    {
                        self.add_quiet_move(
                            Move::construct(
                                self.util,
                                Square::E8,
                                Square::G8,
                                Piece::EMPTs,
                                Piece::EMPTs,
                                moves::CASTLE_FLAG,
                            ),
                            mv_list,
                        );
                        //println!("BK castling");
                    }
                }
            }
            if self.castling & Castling::BQ != 0 {
                if self.pieces[Square::D8] == Piece::EMPTs
                    && self.pieces[Square::C8] == Piece::EMPTs
                    && self.pieces[Square::B1] == Piece::EMPTs
                {
                    if !self.sq_attacked(Square::E8 as i8, Side::WHITE)
                        && !self.sq_attacked(Square::D8 as i8, Side::WHITE)
                    {
                        self.add_quiet_move(
                            Move::construct(
                                self.util,
                                Square::E1,
                                Square::C8,
                                Piece::EMPTs,
                                Piece::EMPTs,
                                moves::CASTLE_FLAG,
                            ),
                            mv_list,
                        );
                        //println!("BQ castling");
                    }
                }
            }
        } else {
            return;
        }
        for pce_cnt in 0..self.piece_count[side_pawn] {
            let sq = self.piece_list[side_pawn][pce_cnt];
            let left_cap = sq as i8 + pawn_offsets[1];
            let right_cap = sq as i8 + pawn_offsets[2];
            let front_sq = sq as i8 + pawn_offsets[0];
            let jump_sq = sq as i8 + pawn_offsets[0] * 2;

            debug_assert!(sq >= 0);
            debug_assert!(left_cap >= 0);
            debug_assert!(right_cap >= 0);
            debug_assert!(front_sq >= 0);
            debug_assert!(jump_sq >= 0);

            let sq = sq as u8;
            let left_cap = left_cap as u8;
            let right_cap = right_cap as u8;
            let front_sq = front_sq as u8;
            let jump_sq = jump_sq as u8;

            debug_assert!(self.util.is_square_valid(sq));
            if self.pieces[front_sq] == Piece::EMPTs {
                self.add_pawn_move(side, sq, front_sq, Piece::EMPTs, mv_list);
                if self.util.ranks[sq] == pawn_starting_rank && self.pieces[jump_sq] == Piece::EMPTs
                {
                    self.add_quiet_move(
                        Move::construct(
                            self.util,
                            sq,
                            jump_sq,
                            Piece::EMPTs,
                            Piece::EMPTs,
                            moves::PAWN_START_FLAG,
                        ),
                        mv_list,
                    );
                }
            }
            if self.util.is_square_valid(left_cap)
                && self.util.piece_colours[self.pieces[left_cap]] == opposing_side
            {
                self.add_pawn_move(side, sq, left_cap, self.pieces[left_cap], mv_list);
            }
            if self.util.is_square_valid(right_cap)
                && self.util.piece_colours[self.pieces[right_cap]] == opposing_side
            {
                self.add_pawn_move(side, sq, right_cap, self.pieces[right_cap], mv_list);
            }
            if left_cap == self.enpassant {
                self.add_capture_move(
                    Move::construct(
                        self.util,
                        sq,
                        left_cap,
                        Piece::EMPTs,
                        Piece::EMPTs,
                        moves::ENPASSANT_FLAG,
                    ),
                    mv_list,
                );
            } else if right_cap == self.enpassant {
                self.add_capture_move(
                    Move::construct(
                        self.util,
                        sq,
                        right_cap,
                        Piece::EMPTs,
                        Piece::EMPTs,
                        moves::ENPASSANT_FLAG,
                    ),
                    mv_list,
                );
            }
        }
        for i in sliding_start_pce..sliding_end_pce {
            let pce = self.util.sliding[i];
            debug_assert!(self.util.is_piece_valid(pce));
            //println!("Sliding piece = {}", pce);
            //match pce {
            //    Piece::WB | Piece::BB => directions = &self.util.bishop_dir,
            //    Piece::WR | Piece::BR => directions = &self.util.rook_dir,
            //    Piece::WQ | Piece::BQ => directions = &self.util.king_queen_dir,
            //    _ => panic!("Unexpected piece in sliding move generation!"),
            //}
            for pce_cnt in 0..self.piece_count[pce] {
                let sq = self.piece_list[pce][pce_cnt];
                debug_assert!(self.util.is_square_valid(sq));
                //println!("Piece {} is on {}", self.util.piece_chars[pce], self.util.sq_to_string(sq));
                for i in 0..self.util.num_dir[pce] {
                    let dir = self.util.piece_dir[(pce, i)];
                    if dir == 0 {
                        break;
                    }
                    let mut offset = sq as i8 + dir;
                    while self.util.is_square_valid(offset as u8) {
                        let offset_pce = self.pieces[offset];
                        if offset_pce != Piece::EMPTs {
                            if self.util.piece_colours[offset_pce] == opposing_side {
                                self.add_capture_move(
                                    Move::construct(
                                        self.util,
                                        sq,
                                        offset as u8,
                                        offset_pce,
                                        Piece::EMPTs,
                                        0,
                                    ),
                                    mv_list,
                                );
                                //println!("Capture on {}", self.util.sq_to_string(offset));
                            }
                            break;
                        }
                        self.add_quiet_move(
                            Move::construct(self.util, sq, offset as u8, Piece::EMPTs, Piece::EMPTs, 0),
                            mv_list,
                        );
                        //println!("Normal move on {}", self.util.sq_to_string(offset));
                        offset += dir;
                    }
                }
            }
        }
        for i in non_sliding_start_pce..non_sliding_end_pce {
            let pce = self.util.sliding[i];
            debug_assert!(self.util.is_piece_valid(pce));
            //println!("Non sliding piece = {}", pce);
            //match pce {
            //    Piece::WN | Piece::BN => directions = &self.util.knight_dir,
            //    Piece::WK | Piece::BK => directions = &self.util.king_queen_dir,
            //    _ => panic!("Unexpected piece in non-sliding move generation!"),
            //}
            for pce_cnt in 0..self.piece_count[pce] {
                let sq = self.piece_list[pce][pce_cnt];
                debug_assert!(self.util.is_square_valid(sq));
                //println!("Piece {} is on {}", self.util.piece_chars[pce], self.util.sq_to_string(sq));
                for i in 0..self.util.num_dir[pce] {
                    let dir = self.util.piece_dir[(pce, i)];
                    if dir == 0 {
                        break;
                    }
                    let offset = sq as i8 + dir;
                    if self.util.is_square_valid(offset as u8) {
                        let offset_pce = self.pieces[offset];
                        if offset_pce != Piece::EMPTs {
                            if self.util.piece_colours[offset_pce] == opposing_side {
                                self.add_capture_move(
                                    Move::construct(
                                        self.util,
                                        sq,
                                        offset as u8,
                                        offset_pce,
                                        Piece::EMPTs,
                                        0,
                                    ),
                                    mv_list,
                                );
                                //println!("Capture on {}", self.util.sq_to_string(offset));
                            }
                            continue;
                        }
                        self.add_quiet_move(
                            Move::construct(self.util, sq, offset as u8, Piece::EMPTs, Piece::EMPTs, 0),
                            mv_list,
                        );
                        //println!("Normal move on {}", self.util.sq_to_string(offset));
                    }
                }
            }
        }
    }
    pub fn add_quiet_move(&self, mv: moves::Move, mv_list: &mut moves::MoveList) {
        mv_list.moves[mv_list.count].mv = mv.mv;
        mv_list.moves[mv_list.count].score = mv.score;
        mv_list.count += 1;
    }
    pub fn add_capture_move(&self, mv: moves::Move, mv_list: &mut moves::MoveList) {
        mv_list.moves[mv_list.count].mv = mv.mv;
        mv_list.moves[mv_list.count].score = mv.score;
        mv_list.count += 1;
    }
    pub fn add_enpassant_move(&self, mv: moves::Move, mv_list: &mut moves::MoveList) {
        mv_list.moves[mv_list.count].mv = mv.mv;
        mv_list.moves[mv_list.count].score = mv.score;
        mv_list.count += 1;
    }
    pub fn add_pawn_move(
        &self,
        side: u8,
        from_sq: u8,
        to_sq: u8,
        capture: u8,
        mv_list: &mut moves::MoveList,
    ) {
        debug_assert!(self.util.is_piece_valid(capture) || capture == Piece::EMPTs);
        debug_assert!(self.util.is_square_valid(from_sq));
        debug_assert!(self.util.is_square_valid(to_sq));

        let add_move = Position::add_quiet_move;
        let mut promotions = &self.util.white_promotions;
        if side == Side::BLACK {
            promotions = &self.util.black_promotions;
        }
        if capture != Piece::EMPTs {
            let add_move = Position::add_capture_move;
        }
        if (side == Side::WHITE && self.util.ranks[from_sq] == Rank::RANK_7)
            || (side == Side::BLACK && self.util.ranks[from_sq] == Rank::RANK_2)
        {
            for p in &promotions.0 {
                add_move(
                    &self,
                    moves::Move::construct(self.util, from_sq, to_sq, capture, *p, 0),
                    mv_list,
                );
            }
        } else {
            add_move(
                &self,
                moves::Move::construct(self.util, from_sq, to_sq, capture, Piece::EMPTs, 0),
                mv_list,
            );
        }
    }

    pub fn test_sq_attacked(&self, side: u8) {
        for rank in (Rank::RANK_1..=Rank::RANK_8).rev() {
            for file in File::FILE_A..=File::FILE_H {
                let sq = self.util.fr_to_sq(file, rank);
                if self.sq_attacked(sq as i8, side) {
                    print!("X")
                } else {
                    print!("-");
                }
            }
            println!();
        }
    }

    pub fn sq_attacked(&self, sq: i8, side: u8) -> bool {
        debug_assert!(self.util.is_square_valid(sq as u8));
        debug_assert!(self.util.is_side_valid(side));
        debug_assert!(self.check_board());

        if side == Side::WHITE {
            if self.pieces[sq - 11] == Piece::WP || self.pieces[sq - 9] == Piece::WP {
                return true;
            }
        } else {
            if self.pieces[sq + 11] == Piece::BP || self.pieces[sq + 9] == Piece::BP {
                return true;
            }
        }
        for i in 0..8 {
            //let pce = self.pieces[sq + self.util.knight_dir[i]];
            let pce = self.pieces[sq + self.util.piece_dir[(Piece::WN, i)]];
            if pce != Square::OFFBOARD && pce != Piece::EMPTs {
                if self.util.is_knight[pce] && self.util.piece_colours[pce] == side {
                    return true;
                }
            }
        }
        for i in 0..4 {
            //let dir = self.util.rook_dir[i];
            let dir = self.util.piece_dir[(Piece::WR, i)];
            let mut offset = sq + dir;
            let mut pce = self.pieces[offset];
            while pce != Square::OFFBOARD {
                if pce != Piece::EMPTs {
                    if self.util.is_rook_queen[pce] && self.util.piece_colours[pce] == side {
                        return true;
                    }
                    break;
                }
                offset += dir;
                pce = self.pieces[offset];
            }
        }
        for i in 0..4 {
            //let dir = self.util.bishop_dir[i];
            let dir = self.util.piece_dir[(Piece::WB, i)];
            let mut offset = sq + dir;
            let mut pce = self.pieces[offset];
            while pce != Square::OFFBOARD {
                if pce != Piece::EMPTs {
                    if self.util.is_bishop_queen[pce] && self.util.piece_colours[pce] == side {
                        return true;
                    }
                    break;
                }
                offset += dir;
                pce = self.pieces[offset];
            }
        }
        for i in 0..8 {
            //let pce = self.pieces[sq + self.util.king_queen_dir[i]];
            let pce = self.pieces[sq + self.util.piece_dir[(Piece::WK, i)]];
            if pce != Square::OFFBOARD && pce != Piece::EMPTs {
                if self.util.is_king[pce] && self.util.piece_colours[pce] == side {
                    return true;
                }
            }
        }
        false
    }

    pub fn check_board(&self) -> bool {
        let mut temp_pos: Position = Position::init(self.util);
        temp_pos.pawns = self.pawns.clone();

        for pce in board::Piece::WP..=board::Piece::BK {
            for pce_cnt in 0..self.piece_count[pce] {
                let sq120 = self.piece_list[pce][pce_cnt];
                debug_assert!(self.pieces[sq120] == pce);
            }
        }

        for sq64 in 0..board::NUM_SQUARES {
            let sq120 = self.util.sq64_to_sq120[sq64];
            let pce = self.pieces[sq120];
            temp_pos.piece_count[pce] += 1;
            let colour = self.util.piece_colours[pce];
            if self.util.is_big_piece[pce] {
                temp_pos.big_pieces[colour] += 1;
            } else if self.util.is_major_piece[pce] {
                temp_pos.major_pieces[colour] += 1;
            } else if self.util.is_minor_piece[pce] {
                temp_pos.minor_pieces[colour] += 1;
            }
            if pce != Piece::EMPTs {
                temp_pos.material[colour] += self.util.piece_values[pce];
            }
        }

        for pce in board::Piece::WP..=board::Piece::BK {
            debug_assert!(temp_pos.piece_count[pce] == self.piece_count[pce]);
        }

        let mut pawn_cnt = temp_pos.pawns[board::Side::WHITE].count_bits();
        debug_assert!(pawn_cnt == self.piece_count[board::Piece::WP]);
        pawn_cnt = temp_pos.pawns[board::Side::BLACK].count_bits();
        debug_assert!(pawn_cnt == self.piece_count[board::Piece::BP]);
        pawn_cnt = temp_pos.pawns[board::Side::BOTH].count_bits();
        debug_assert!(
            pawn_cnt == self.piece_count[board::Piece::WP] + self.piece_count[board::Piece::BP]
        );

        while temp_pos.pawns[board::Side::WHITE].val != 0 {
            let sq64 = temp_pos.pawns[board::Side::WHITE].pop_bit();
            debug_assert!(self.pieces[self.util.sq64_to_sq120[sq64]] == board::Piece::WP);
        }

        while temp_pos.pawns[board::Side::BLACK].val != 0 {
            let sq64 = temp_pos.pawns[board::Side::BLACK].pop_bit();
            debug_assert!(self.pieces[self.util.sq64_to_sq120[sq64]] == board::Piece::BP);
        }

        while temp_pos.pawns[board::Side::BOTH].val != 0 {
            let sq64 = temp_pos.pawns[board::Side::BOTH].pop_bit();
            debug_assert!(
                self.pieces[self.util.sq64_to_sq120[sq64]] == board::Piece::WP
                    || self.pieces[self.util.sq64_to_sq120[sq64]] == board::Piece::BP
            );
        }

        debug_assert!(self.side == board::Side::WHITE || self.side == board::Side::BLACK);
        debug_assert!(self.util.gen_pos_key(self) == self.key);

        debug_assert!(
            self.enpassant == board::Square::NONE
                || (self.util.ranks[self.enpassant] == board::Rank::RANK_6
                    && self.side == board::Side::WHITE)
                || (self.util.ranks[self.enpassant] == board::Rank::RANK_3
                    && self.side == board::Side::BLACK)
        );

        debug_assert!(self.pieces[self.king_squares[Side::WHITE]] == Piece::WK);
        debug_assert!(self.pieces[self.king_squares[Side::BLACK]] == Piece::BK);

        true
    }

    pub fn update_material(&mut self) {
        for i in 0..board::REPR_NUM_SQUARES {
            let sq = i as u8;
            let pce = self.pieces[i];
            if pce != board::Square::OFFBOARD && pce != board::Piece::EMPTs {
                let colour = self.util.piece_colours[pce];

                if self.util.is_big_piece[pce] {
                    self.big_pieces[colour] += 1;
                }
                if self.util.is_major_piece[pce] {
                    self.major_pieces[colour] += 1;
                }
                if self.util.is_minor_piece[pce] {
                    self.minor_pieces[colour] += 1;
                }
                self.material[colour] += self.util.piece_values[pce];
                self.piece_list[pce][self.piece_count[pce]] = sq;
                self.piece_count[pce] += 1;
                match pce {
                    board::Piece::WK | board::Piece::BK => self.king_squares[colour] = sq,
                    board::Piece::WP => {
                        self.pawns[board::Side::WHITE].set_bit(self.util.sq120_to_sq64[sq]);
                        self.pawns[board::Side::BOTH].set_bit(self.util.sq120_to_sq64[sq]);
                    }
                    board::Piece::BP => {
                        self.pawns[board::Side::BLACK].set_bit(self.util.sq120_to_sq64[sq]);
                        self.pawns[board::Side::BOTH].set_bit(self.util.sq120_to_sq64[sq]);
                    }
                    _ => (),
                }
            }
        }
    }

    pub fn print(&self) {
        let mut sq;
        for rank in (board::Rank::RANK_1..=board::Rank::RANK_8).rev() {
            print!("{}  ", rank + 1);
            for file in board::File::FILE_A..=board::File::FILE_H {
                sq = self.util.fr_to_sq(file, rank);
                print!("{:3}", self.util.piece_chars[self.pieces[sq]]);
            }
            print!("\n");
        }
        print!("   ");
        for file in board::File::FILE_A..=board::File::FILE_H {
            print!("{:3}", ('a' as u8 + file) as char);
        }
        println!("\nSide: {}", self.util.side_chars[self.side]);
        println!("Enpassant: {}", self.enpassant);
        println!(
            "Castling: {} {} {} {}",
            if self.castling & Castling::WK != 0 {
                'K'
            } else {
                '-'
            },
            if self.castling & Castling::WQ != 0 {
                'Q'
            } else {
                '-'
            },
            if self.castling & Castling::BK != 0 {
                'k'
            } else {
                '-'
            },
            if self.castling & Castling::BQ != 0 {
                'q'
            } else {
                '-'
            }
        );
        println!("Key: {:X}", self.key);
        println!("Material: {:?}", self.material);
    }

    pub fn reset_board(&mut self) {
        for i in 0..board::REPR_NUM_SQUARES {
            self.pieces[i] = board::Square::OFFBOARD;
        }

        for i in 0..board::NUM_SQUARES {
            self.pieces[self.util.sq64_to_sq120[i]] = board::Piece::EMPTs;
        }

        for i in 0..2 {
            self.big_pieces[i] = 0;
            self.major_pieces[i] = 0;
            self.minor_pieces[i] = 0;
            self.material[i] = 0;
        }

        for i in 0..3 {
            self.pawns[i].val = 0u64;
        }

        for i in 0..13 {
            self.piece_count[i] = 0;
        }

        self.king_squares[board::Side::WHITE] = board::Square::NONE;
        self.king_squares[board::Side::BLACK] = board::Square::NONE;
        self.side = board::Side::BOTH;
        self.enpassant = board::Square::NONE;
        self.fifty_moves = 0;
        self.ply = 0;
        self.hist_ply = 0;
        self.castling = 0;
        self.key = 0u64;
    }

    pub fn parse_fen(&mut self, fen: String) {
        let mut rank = board::Rank::RANK_8 as i8;
        let mut file = board::File::FILE_A;
        let mut piece;
        let mut sq;
        let mut sq64;
        let mut count;

        self.reset_board();

        let mut fen_iter = fen.chars();
        let mut ch;

        while rank >= board::Rank::RANK_1 as i8 {
            ch = fen_iter.next().expect("Expected side FEN");
            count = 1;
            match ch {
                'p' => piece = board::Piece::BP,
                'r' => piece = board::Piece::BR,
                'n' => piece = board::Piece::BN,
                'b' => piece = board::Piece::BB,
                'k' => piece = board::Piece::BK,
                'q' => piece = board::Piece::BQ,
                'P' => piece = board::Piece::WP,
                'R' => piece = board::Piece::WR,
                'N' => piece = board::Piece::WN,
                'B' => piece = board::Piece::WB,
                'K' => piece = board::Piece::WK,
                'Q' => piece = board::Piece::WQ,
                '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' => {
                    piece = board::Piece::EMPTs;
                    count = ch.to_digit(10).expect("Expected digit character");
                }
                '/' | ' ' => {
                    rank -= 1;
                    file = board::File::FILE_A;
                    continue;
                }
                _ => panic!("Invalid FEN: {}. Unexpected character {}", fen, ch),
            }

            for _ in 0..count {
                sq64 = rank * 8 + file as i8;
                sq = self.util.sq64_to_sq120[sq64];
                if piece != board::Piece::EMPTs {
                    self.pieces[sq] = piece;
                }
                file += 1;
            }
        }

        ch = fen_iter.next().expect("Expected side FEN");
        debug_assert!(ch == 'w' || ch == 'b');
        match ch {
            'w' => self.side = board::Side::WHITE,
            'b' => self.side = board::Side::BLACK,
            _ => panic!("Expected side FEN"),
        }

        fen_iter.next();

        for _ in 0..4 {
            ch = fen_iter.next().expect("Expected castling FEN");
            match ch {
                ' ' => break,
                'K' => self.castling |= board::Castling::WK,
                'Q' => self.castling |= board::Castling::WQ,
                'k' => self.castling |= board::Castling::BK,
                'q' => self.castling |= board::Castling::BQ,
                _ => break,
                //                _ => panic!("Unexpected character while parsing castling FEN: {}", ch),
            }
        }
        ch = fen_iter.next().expect("Expected whitespace");

        debug_assert!(self.castling >= 0 && self.castling <= 15);

        ch = fen_iter.next().expect("Expected enpassant FEN");

        if ch != '-' {
            file = ch as u8 - 'a' as u8;
            rank = fen_iter.next().expect("Expected enpassant rank") as i8 - '1' as i8;

            //println!("file: {}, rank: {}", file, rank);

            debug_assert!(file >= board::File::FILE_A && file <= board::File::FILE_H);
            debug_assert!(rank >= board::Rank::RANK_1 as i8 && rank <= board::Rank::RANK_8 as i8);

            self.enpassant = self.util.fr_to_sq(file, rank as u8);
        }

        self.key = self.util.gen_pos_key(self);
        self.update_material();
    }
}
