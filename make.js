const fs = require('fs');
const path = require('path');
const process = require('process');
const packageConfig = require('./package.json');
const {execSync} = require('child_process');

const checkPackageConfig = () => {
    return packageConfig && packageConfig.make_args;
}

const checkProcessArgs = () => {
    // 获取命令参数
    const args = process.argv.slice(2);
    if (args.length === 0) {
        return "build"
    }
    return args[0];
}

const processMakeArgs = (makeArgs) => {
    makeArgs.src = makeArgs.src || ['./'];
    makeArgs.target = makeArgs.target || 'a.out';
    makeArgs.output = makeArgs.output || 'obj';
    makeArgs.cc = makeArgs.cc || 'gcc';
    makeArgs.include = makeArgs.include || ['./'];
    return makeArgs;
}

const processDir = (dir) => {
    return dir.startsWith(".") ? dir.substring(1, dir.length) : dir;
}

const build = (makeArgs) => {
    const cpp_files = []

    makeArgs.src.forEach((src) => {
        const srcPath = path.join(__dirname, src);

        if (!fs.existsSync(srcPath)) {
            console.log('src path not exist:', src);
            process.exit(-1);
        }
        // 扫描目录下所有.cpp文件
        cpp_files.push(...fs.readdirSync(srcPath)
            .filter(file => file.endsWith('.cpp'))
            .map((filename) => ({
                filename,
                dir: processDir(src)
            })));
    });

    const {output, target, cc, include} = makeArgs;

    fs.mkdirSync(path.join(__dirname, output), {recursive: true});
    const cmd_s = []

    cmd_s.push(cc)

    include.forEach((include) => {
        cmd_s.push('-I' + include)
    })

    if (makeArgs.cxx_flags) {
        cmd_s.push(makeArgs.cxx_flags)
    }

    if (makeArgs.ld_flags) {
        cmd_s.push(makeArgs.ld_flags)
    }

    // 生成编译命令
    const buildCmd = cmd_s.join(' ');

    // 执行编译命令
    cpp_files.forEach((cpp_file) => {
        const obj_file = path.join(__dirname, output, cpp_file.filename.replace('.cpp', '.o'));
        const cmd = buildCmd + ' -c ' + path.join(__dirname, cpp_file.dir, cpp_file.filename) + ' -o ' + obj_file;
        console.log(cmd);
        const ret = execSync(cmd);
        console.log(ret.toString());
        cmd_s.push(obj_file);
    });

    // 生成链接命令
    cmd_s.push('-o ' + path.join(__dirname, target));
    const linkCmd = cmd_s.join(' ');
    console.log(linkCmd);
    const ret = execSync(linkCmd);
    console.log(ret.toString());
}

const clean = (makeArgs) => {
    const {output, target} = makeArgs;
    // 删除生成的exe文件
    fs.unlinkSync(path.join(__dirname, target));
    console.log('unlink ' + path.join(__dirname, target));
    // 删除生成的obj文件
    fs.rmdirSync(path.join(__dirname, output), {recursive: true});
    console.log('rmdir ' + path.join(__dirname, output));
}

const main = () => {
    // 1 检查当前目录是否存在package.json
    if (!checkPackageConfig()) {
        console.log('package.json文件不存在');
        process.exit(-1);
    }

    const makeArgs = packageConfig.make_args;
    console.log('make ', makeArgs.target, ' start...');

    const cmd = checkProcessArgs()
    switch (cmd) {
        case 'build':
            build(processMakeArgs(makeArgs));
            break;
        case 'clean':
            clean(processMakeArgs(makeArgs));
            break;
        default:
            console.log('Usage: node make.js [build|clean]');
            process.exit(0);
    }
    console.log('make ', makeArgs.target, ' end...');
}

main();
