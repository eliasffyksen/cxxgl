{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
    nativeBuildInputs = with pkgs; [
      gnumake clang glfw glew stb glm
    ];

    shellHook = ''
      export CXX="clang++"
    '';
}
