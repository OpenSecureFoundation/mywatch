
#!/usr/bin/env bash
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

PASS=0
FAIL=0
BINARY="../mywatch"
section() {
    echo ""
    echo -e "${BLUE}══════════════════════════════════════${NC}"
    echo -e "${BLUE}  $1${NC}"
    echo -e "${BLUE}══════════════════════════════════════${NC}"
}

ok() {
    local desc="$1"; shift
    if eval "$@" > /dev/null 2>&1; then
        echo -e "  ${GREEN}[PASS]${NC} $desc"; PASS=$((PASS+1))
    else
        echo -e "  ${RED}[FAIL]${NC} $desc"; FAIL=$((FAIL+1))
    fi
}

fail_expected() {
    local desc="$1"; shift
    if ! eval "$@" > /dev/null 2>&1; then
        echo -e "  ${GREEN}[PASS]${NC} $desc (echec attendu)"; PASS=$((PASS+1))
    else
        echo -e "  ${RED}[FAIL]${NC} $desc (aurait du echouer)"; FAIL=$((FAIL+1))
    fi
}

pre_check() {
    section "Verification de l'environnement"
    if [ ! -f "$BINARY" ]; then
        echo -e "${RED}ERREUR : binaire '$BINARY' introuvable.${NC}"
        echo -e "${YELLOW}Conseil : lancez 'make' dans le dossier mywatch/ avant les tests.${NC}"
        exit 1
    fi
    echo -e "  ${GREEN}[OK]${NC} Binaire '$BINARY' trouve"
    [ -x "$BINARY" ] && echo -e "  ${GREEN}[OK]${NC} Binaire executable" \
                     || { echo -e "${RED}ERREUR : non executable${NC}"; exit 1; }
}

test_bad_args() {
    section "Arguments invalides"
    fail_expected "Aucune commande fournie"   "timeout 2 $BINARY"
    fail_expected "Option inconnue -z"        "timeout 2 $BINARY -z date"
}

test_option_n() {
    section "Option -n (intervalle de rafraichissement)"
    ok "Lance avec -n 1 date sans erreur"   "timeout 3 $BINARY -n 1 date"
    ok "Lance avec -n 0.5 date sans erreur" "timeout 2 $BINARY -n 0.5 date"

    local t_start t_end elapsed
    t_start=$(date +%s%N)
    timeout 2.5 "$BINARY" -n 2 date > /dev/null 2>&1
    t_end=$(date +%s%N)
    elapsed=$(( (t_end - t_start) / 1000000 ))
    if [ "$elapsed" -ge 1800 ] && [ "$elapsed" -le 3200 ]; then
        echo -e "  ${GREEN}[PASS]${NC} Intervalle -n 2 respecte (~${elapsed}ms)"; PASS=$((PASS+1))
    else
        echo -e "  ${RED}[FAIL]${NC} Intervalle -n 2 non respecte (${elapsed}ms, attendu ~2000ms)"; FAIL=$((FAIL+1))
    fi
}

test_option_t() {
    section "Option -t (desactiver l'en-tete)"
    ok "Lance avec -t date sans erreur" "timeout 2 $BINARY -t date"
}

test_option_e() {
    section "Option -e (quitter sur erreur de commande)"
    ok "Lance avec -e et commande valide" "timeout 3 $BINARY -e date"

    local exit_code
    timeout 3 "$BINARY" -e commande_qui_nexiste_pas_du_tout > /dev/null 2>&1
    exit_code=$?
    if [ "$exit_code" -ne 0 ]; then
        echo -e "  ${GREEN}[PASS]${NC} -e quitte quand la commande echoue"; PASS=$((PASS+1))
    else
        echo -e "  ${RED}[FAIL]${NC} -e aurait du quitter sur commande invalide"; FAIL=$((FAIL+1))
    fi
}

test_option_d() {
    section "Option -d (highlight des differences)"
    ok "Lance avec -d ls sans erreur" "timeout 3 $BINARY -d ls /tmp"
}

test_combinations() {
    section "Combinaisons d'options"
    ok "Combinaison -n 1 -d date"    "timeout 3 $BINARY -n 1 -d date"
    ok "Combinaison -n 1 -t date"    "timeout 3 $BINARY -n 1 -t date"
    ok "Combinaison -n 1 -d -t date" "timeout 3 $BINARY -n 1 -d -t date"
}

test_commands() {
    section "Commandes courantes"
    ok "watch cat /proc/loadavg" "timeout 3 $BINARY -n 1 cat /proc/loadavg"
    ok "watch df -h"             "timeout 3 $BINARY -n 1 df -h"
    ok "watch ls -l /tmp"        "timeout 3 $BINARY -n 1 ls -l /tmp"
    ok "watch echo hello world"  "timeout 3 $BINARY -n 1 echo hello world"
}

summary() {
    local total=$((PASS + FAIL))
    echo ""
    echo -e "${BLUE}══════════════════════════════════════${NC}"
    echo -e "${BLUE}  BILAN DES TESTS${NC}"
    echo -e "${BLUE}══════════════════════════════════════${NC}"
    echo -e "  Total   : $total"
    echo -e "  ${GREEN}Passes  : $PASS${NC}"
    [ "$FAIL" -gt 0 ] \
        && echo -e "  ${RED}Echoues : $FAIL${NC}" \
        || echo -e "  Echoues : $FAIL"
    echo ""
    [ "$FAIL" -eq 0 ] \
        && echo -e "  ${GREEN}Tous les tests sont passes !${NC}" \
        || echo -e "  ${YELLOW}$FAIL test(s) echoue(s).${NC}"
    echo ""
}

main() {
    echo ""
    echo -e "${BLUE}  mywatch — Tests automatiques (Gregory)${NC}"
    pre_check
    test_bad_args
    test_option_n
    test_option_t
    test_option_e
    test_option_d
    test_combinations
    test_commands
    summary
    [ "$FAIL" -eq 0 ] && exit 0 || exit 1
}

main "$@"
