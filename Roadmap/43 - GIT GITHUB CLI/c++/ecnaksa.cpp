/*
 * #43 - GIT / GITHUB CLI (C++)
 *
 * =========================== TEORÍA ===========================
 * Integración con el sistema: se invoca el binario 'git' con popen() para
 * capturar su salida. Cada opción del CLI corresponde a comandos de Git
 * (init, branch, add, commit, log...). La demo trabaja sobre un repo temporal.
 *
 * ============================ PRÁCTICA ========================
 */

#include <iostream>
#include <string>
#include <cstdio>
#include <array>

static std::string run(const std::string& cmd) {
    std::string out; std::array<char, 2048> buf{};
    FILE* p = popen((cmd + " 2>&1").c_str(), "r");
    if (!p) return "";
    size_t n; while ((n = fread(buf.data(), 1, buf.size(), p)) > 0) out.append(buf.data(), n);
    pclose(p);
    return out;
}

int main() {
    std::cout << "=== Git CLI (demo sobre repo temporal) ===\n";
    std::string dir = "/tmp/git_demo_cpp";
    run("rm -rf " + dir + " && mkdir -p " + dir);
    std::string git = "git -C " + dir + " ";

    std::cout << "2) init:   " << run(git + "init -b main");
    run(git + "config user.email demo@demo.com");
    run(git + "config user.name demo");
    run("echo hola > " + dir + "/hola.txt");
    std::cout << "5) status:\n" << run(git + "status --short");
    run(git + "add .");
    std::cout << "6) commit: " << run(git + "commit -m 'primer commit' -q; echo commit hecho");
    std::cout << "3) branch: "; run(git + "branch feature"); std::cout << "rama 'feature' creada\n";
    std::cout << "7) log:    " << run(git + "log --oneline");

    run("rm -rf " + dir);
    std::cout << "(repositorio temporal eliminado)\n";
    return 0;
}
