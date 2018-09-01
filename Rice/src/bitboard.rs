use board;

#[derive(Copy, Clone)]
pub struct BitBoard<'a> {
    pub val: u64,
    pub util: &'a board::Util,
}

impl<'a> BitBoard<'a> {
    pub fn init(util: &'a board::Util) -> BitBoard<'a> {
        BitBoard {
            val: 0u64,
            util: util,
        }
    }

    pub fn print(&self) {
        let shift = 1u64;
        let mut sq;
        let mut sq64;
        for rank in (board::Rank::RANK_1..=board::Rank::RANK_8).rev() {
            for file in board::File::FILE_B..=board::File::FILE_H {
                sq = self.util.fr_to_sq(file, rank);
                sq64 = self.util.sq120_to_sq64[sq];
                if (shift << sq64) & self.val != 0 {
                    print!("X");
                } else {
                    print!("-");
                }
            }
            print!("\n");
        }
    }

    pub fn count_bits(&self) -> u8 {
        let mut r = 0;
        let mut b = self.val;
        while b != 0 {
            r += 1;
            b &= b - 1;
        }
        r
    }

    pub fn set_bit(&mut self, sq: u8) {
        self.val |= self.util.set_masks[sq];
    }

    pub fn clear_bit(&mut self, sq: u8) {
        self.val &= self.util.clear_masks[sq];
    }

    pub fn pop_bit(&mut self) -> u8 {
        let b = self.val ^ (self.val - 1);
        let fold = ((b & 0xffffffff) ^ (b >> 32)) as u32;
        self.val &= self.val - 1;

        //        println!("Fold res: {}", ((b & 0xffffffff) ^ (b >> 32)));
        //        println!("Fold: {}, Fold (wrapped): {}", fold, fold.wrapping_mul(0x783a9b23) >> 26);

        self.util.bit_table[(fold.wrapping_mul(0x783a9b23) >> 26)]
    }
}
