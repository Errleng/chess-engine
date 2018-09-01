#![allow(dead_code)]
extern crate num_traits;
extern crate rand;
//#[macro_use]
//extern crate enum_primitive;
//extern crate num_traits;

pub mod bitboard;
pub mod board;
pub mod moves;
pub mod position;
pub mod types;

fn main() {
    println!("START\n");
    let mut globals: board::Util = Default::default();
    //    println!("{:?}", &global.sq64_to_sq120[..]);
    //    println!("{:?}", &global.sq120_to_sq64[..]);
    globals.init();
    //    println!("{:?}", &global.sq64_to_sq120[..]);
    //    println!("{:?}", &global.sq120_to_sq64[..]);

    for i in 0..globals.sq64_to_sq120.len() {
        if i % 8 == 0 {
            print!("\n");
        }
        print!("{:5}", globals.sq64_to_sq120[i]);
    }
    println!();

    for i in 0..globals.sq120_to_sq64.len() {
        if i % 10 == 0 {
            print!("\n");
        }
        print!("{:5}", globals.sq120_to_sq64[i]);
    }
    println!();

    let mut bitboard_test: bitboard::BitBoard = bitboard::BitBoard::init(&globals);
    bitboard_test.print();
    bitboard_test.set_bit(board::Square::D2);
    bitboard_test.set_bit(board::Square::D3);
    bitboard_test.set_bit(board::Square::D4);
    println!();
    bitboard_test.print();
    println!("Bitboard value: {}", bitboard_test.val);
    println!("There are {} bits set", bitboard_test.count_bits());

    while bitboard_test.val != 0 {
        println!("Popped LSB at index {}", bitboard_test.pop_bit());
        bitboard_test.print();
    }

    //    for i in 0..board::NUM_SQUARES {
    //        println!("Index: {}", i);
    //        let mask_bb = bitboard::BitBoard { bb: global.set_masks[i] };
    //        mask_bb.print();
    //    }
    //
    //    for i in 0..board::NUM_SQUARES {
    //        println!("Index: {}", i);
    //        let mask_bb = bitboard::BitBoard { bb: global.clear_masks[i] };
    //        mask_bb.print();
    //    }

    let mut pos_test: position::Position = position::Position::init(&globals);
    let fen1 = String::from("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    let fen2 = String::from("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1");
    let fen3 = String::from("rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2");
    let fen4 = String::from("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1");
    let fen5 = String::from("k7/3q1p2/8/5P2/4Q3/8/8/K7 w - - 0 2");
    pos_test.parse_fen(fen1);
    pos_test.print();
    pos_test.parse_fen(fen2);
    pos_test.print();
    pos_test.parse_fen(fen3);
    pos_test.print();
    pos_test.parse_fen(fen4);
    pos_test.print();

    for i in 0..board::REPR_NUM_SQUARES {
        if i % 10 == 0 && i != 0 {
            println!();
        }
        print!("{:4}", globals.files[i]);
    }
    println!();

    for i in 0..board::REPR_NUM_SQUARES {
        if i % 10 == 0 && i != 0 {
            println!();
        }
        print!("{:4}", globals.ranks[i]);
    }
    println!();

    pos_test.pawns[board::Side::WHITE].print();
    println!();
    pos_test.pawns[board::Side::BLACK].print();
    println!();
    pos_test.pawns[board::Side::BOTH].print();

    pos_test.print();

    pos_test.check_board();

    //    pos_test.piece_count[board::Piece::WP] -= 1;
    //    pos_test.key ^= global.side_key;

    //    pos_test.check_board();

    pos_test.parse_fen(fen5);
    pos_test.print();
    pos_test.test_sq_attacked(board::Side::WHITE);
    println!();
    pos_test.test_sq_attacked(board::Side::BLACK);

    let from = board::Square::A2;
    let to = board::Square::H7;
    let cap = board::Piece::WR;
    let prom = board::Piece::BQ;
    let mut test_move: moves::Move = moves::Move::construct(&globals, from, to, cap, prom, 0);

    println!("Move Hex: {:X}\nBinary: {:b}", test_move.mv, test_move.mv);
    println!("from: {}, to: {}", test_move.from_sq(), test_move.to_sq());
    println!(
        "captured: {}, promoted: {}",
        test_move.captured(),
        test_move.promoted()
    );
    test_move.set_pawn_start();
    println!("Is pawn start: {}", test_move.is_pawn_start());
    println!(
        "Algebraic form: {}\nfrom: {}\nto: {}",
        test_move.to_string(),
        globals.sq_to_string(from),
        globals.sq_to_string(to)
    );

    let pawn_moves_test_white =
        String::from("rnbqk2r/pp1p1pPp/8/2p1pPb1/1P1P4/N2P1NQP/PBP1P1B1/R3K2R b KQkq - 1 1 ");
    let knight_moves_test_black = String::from("5k2/1n6/4n3/6N1/8/3N4/8/5K2 b - -  0 1");
    let bishops_moves_test_black = String::from("6k1/1b6/4n3/8/1n4B1/1B3N2/1N6/2b3K1 b - - 0 1");
    let rook_moves_test_black = String::from("6k1/8/5r2/8/1nR5/5N2/8/6K1 b - - 0 1");
    let queen_moves_test_black = String::from("6k1/8/4nq2/8/1nQ5/5N2/1N6/6K1 b - - 0 1");
    let gen_moves_test_white =
        String::from("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1");
    pos_test.parse_fen(pawn_moves_test_white);
    pos_test.print();
    let mut test_mv_list = moves::MoveList::init(&globals);
    println!("WHITE");
    pos_test.gen_moves(&mut test_mv_list, board::Side::WHITE);
    test_mv_list.print();

    println!("BLACK");
    pos_test.gen_moves(&mut test_mv_list, board::Side::BLACK);
    test_mv_list.print();

    pos_test.parse_fen(gen_moves_test_white);
    pos_test.print();
    pos_test.gen_moves(&mut test_mv_list, board::Side::WHITE);
    test_mv_list.print();

    //    pos_test.parse_fen(knight_moves_test_black);
    //    pos_test.print();
    //    println!("BLACK");
    //    pos_test.gen_moves(&mut test_mv_list, board::Side::BLACK);
    //    test_mv_list.print();
    //    pos_test.gen_moves(&mut test_mv_list, board::Side::WHITE);
    //    test_mv_list.print();
    //
    //    pos_test.parse_fen(bishops_moves_test_black);
    //    pos_test.print();
    //    println!("BLACK");
    //    pos_test.gen_moves(&mut test_mv_list, board::Side::BLACK);
    //    test_mv_list.print();
    //    println!("WHITE");
    //    pos_test.gen_moves(&mut test_mv_list, board::Side::WHITE);
    //    test_mv_list.print();
    //
    //    pos_test.parse_fen(rook_moves_test_black);
    //    pos_test.print();
    //    println!("BLACK");
    //    pos_test.gen_moves(&mut test_mv_list, board::Side::BLACK);
    //    test_mv_list.print();
    //    println!("WHITE");
    //    pos_test.gen_moves(&mut test_mv_list, board::Side::WHITE);
    //    test_mv_list.print();
    //
    //    pos_test.parse_fen(queen_moves_test_black);
    //    pos_test.print();
    //    println!("BLACK");
    //    pos_test.gen_moves(&mut test_mv_list, board::Side::BLACK);
    //    test_mv_list.print();
    //    println!("WHITE");
    //    pos_test.gen_moves(&mut test_mv_list, board::Side::WHITE);
    //    test_mv_list.print();

    println!("\nEND");
}
