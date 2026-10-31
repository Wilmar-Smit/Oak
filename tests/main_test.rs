pub use pretty_assertions::{assert_eq, assert_ne};
#[test]
fn test_sanity_check() {
    let result = 5 + 5;
    assert_eq!(result, 10, "Math sanity check failed!");
}
